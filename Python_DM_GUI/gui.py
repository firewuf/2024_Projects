import tkinter
from tkinter import messagebox
from time import time
import tkinter.filedialog
import Profile
import ds_messenger
import pathlib
from ds_client import CreateSocketError, SendRecvDataError


class DSGUI(tkinter.Tk):
    def __init__(self):
        super().__init__()

        # Dependent on the DSU file open
        self.dsu_prof: Profile.Profile = None
        self.dm_recipients: list = None
        self.dm_lb: tkinter.Listbox = None
        self.new_dm_b: tkinter.Button = None
        self.ds_m: ds_messenger.DirectMessenger = None
        self.menu_file: tkinter.Menu = None
        self.menu_settings: tkinter.Menu = None

        # Dependent on the open chat
        self.current_recipient: str = None
        self.conversation_text: tkinter.Text = None
        self.new_message_field: tkinter.Text = None
        self.send_message_b: tkinter.Button = None

        self._draw()

    def _draw(self):
        self.title("DS App")

        self.minsize(700, 500)
        self.geometry("700x500")

        self.grid_rowconfigure(0, weight=3)
        self.grid_rowconfigure(1, weight=3)
        self.grid_columnconfigure(0, weight=1)
        self.grid_columnconfigure(1, weight=3)

        # Menu Bar
        menu_bar = tkinter.Menu(self)

        self.menu_file = tkinter.Menu(menu_bar, tearoff=0)
        self.menu_file.add_command(
            label="New Profile...", command=self._new_profile
        )
        self.menu_file.add_command(
            label="Open Profile...", command=self._open_profile
        )
        self.menu_file.add_command(
            label="Save Profile", command=self._save_profile
        )
        self.menu_file.entryconfig("Save Profile", state="disabled")
        menu_bar.add_cascade(label="File", menu=self.menu_file)

        self.menu_settings = tkinter.Menu(menu_bar, tearoff=0)
        self.menu_settings.add_command(
            label="Profile Settings", command=self._profile_settings
        )
        self.menu_settings.entryconfig("Profile Settings", state="disabled")
        self.menu_settings.add_command(
            label="Reset Storage", command=self._reset_storage
        )
        self.menu_settings.entryconfig("Reset Storage", state="disabled")
        menu_bar.add_cascade(label="Settings", menu=self.menu_settings)

        self.configure(menu=menu_bar)

        # Left Panel
        self.dm_lb = tkinter.Listbox(self)
        self.dm_lb.bind(
            "<<ListboxSelect>>",
            lambda event: (
                self._open_update_dm_chat(
                    self.dm_recipients[event.widget.curselection()[0]]
                )
                if len(event.widget.curselection()) > 0
                else None
            ),
        )
        self.new_dm_b = tkinter.Button(
            self, text="Add User", command=self._new_dm
        )
        self.new_dm_b.config(state="disabled")

        self.dm_lb.grid(row=0, column=0, rowspan=2, sticky="nsew")
        self.new_dm_b.grid(row=2, column=0, sticky="e")

        # Right Frame
        right_frame = tkinter.Frame(self)
        right_frame.grid_rowconfigure(0, weight=3)
        right_frame.grid_rowconfigure(1, weight=1)
        right_frame.grid_columnconfigure(0, weight=1)
        self.conversation_text = tkinter.Text(right_frame, height=7, width=60)
        self.conversation_text.configure(state="disabled")
        conversation_scrollbar = tkinter.Scrollbar(
            self.conversation_text,
            orient="vertical",
            command=self.conversation_text.yview,
        )
        conversation_scrollbar.pack(side="right", fill="y")
        self.conversation_text["yscrollcommand"] = conversation_scrollbar.set
        self.new_message_field = tkinter.Text(right_frame, height=3, width=60)
        self.new_message_field.config(state="disabled")
        self.send_message_b = tkinter.Button(
            self,
            text="Send Message",
            command=lambda: self._send_message(self.current_recipient),
        )
        self.send_message_b.config(state="disabled")

        right_frame.grid(row=0, column=1, rowspan=2, sticky="nsew")
        self.conversation_text.grid(row=0, column=0, sticky="nsew")
        self.new_message_field.grid(row=1, column=0, sticky="nsew")
        self.send_message_b.grid(row=2, column=1, sticky="e")

        self.after(5000, self._refresh_data)

        self.mainloop()

    def _refresh_data(self):
        self._create_server_connection(True)
        self._check_new_messages()
        if self.dsu_prof:
            self._add_dm_lb_options()
        if self.current_recipient is not None:
            self._open_update_dm_chat(self.current_recipient, True)

        self.after(5000, self._refresh_data)

    def _open_update_dm_chat(self, dm_recip: str, update: bool = False):
        self.dsu_prof.sort_direct_messages()
        convo: list = self.dsu_prof.get_dm_conversation(dm_recip)
        if not update:
            self.current_recipient = dm_recip

        self.conversation_text.configure(state="normal")
        self.conversation_text.delete(1.0, tkinter.END)
        line: float = 1.0
        for msg in convo:
            orator: str = ""
            if msg["me"]:
                orator = "You"
            else:
                orator = "Them"

            self.conversation_text.insert(
                line, f"{orator}: {msg['message']}\n"
            )
            line += 1
        self.conversation_text.configure(state="disabled")
        self.new_message_field.config(state="normal")
        self.send_message_b.config(state="normal")

    def _disable_enable_menu_bar(self, disable: bool):
        if disable:
            new_state = "disabled"
        else:
            new_state = "normal"

        self.menu_file.entryconfig("New Profile...", state=new_state)
        self.menu_file.entryconfig("Open Profile...", state=new_state)
        if (disable) or (not disable and not self.dsu_prof is None):
            self.menu_file.entryconfig("Save Profile", state=new_state)

            self.menu_settings.entryconfig(
                "Profile Settings", state=new_state
            )
            self.menu_settings.entryconfig("Reset Storage", state=new_state)

    def _new_profile(self):
        create_new_profile = NewProfileWindow()
        create_new_profile.transient(self)
        self._disable_enable_menu_bar(True)
        self.wait_window(create_new_profile)

        if (
            create_new_profile.dsuserver
            and create_new_profile.username
            and create_new_profile.password
            and create_new_profile.path
        ):
            if self.dsu_prof:
                self._save_profile()
            self.dsu_prof = Profile.Profile(
                create_new_profile.dsuserver,
                create_new_profile.username,
                create_new_profile.password,
                create_new_profile.path,
            )
            self._reset_gui()
            self._create_server_connection()

            self.new_dm_b.configure(state="normal")
        self._disable_enable_menu_bar(False)

    def _create_server_connection(
        self, silence_warning: bool = False, settings_changed: bool = False
    ):
        if self.dsu_prof and (settings_changed or not self.ds_m):
            try:
                self.ds_m = ds_messenger.DirectMessenger(
                    self.dsu_prof.get_dsuserver(),
                    self.dsu_prof.get_usr(),
                    self.dsu_prof.get_pwd(),
                )
            except CreateSocketError:
                if not silence_warning:
                    messagebox.showerror(
                        "Error Establishing Connection",
                        "There was a problem establishing a connection with the server.",
                    )
            except SendRecvDataError:
                if not silence_warning:
                    messagebox.showerror(
                        "Error Sending or Recieving Data",
                        "There was a problem sending or recieving data to/from the server.",
                    )

    def _open_profile(self):
        self._disable_enable_menu_bar(True)
        p_path = tkinter.filedialog.askopenfilename(
            filetypes=[("DSU files", "*.dsu")]
        )
        if p_path:
            p = Profile.Profile()
            try:
                p.load_profile(p_path)
                if self.dsu_prof:
                    self._save_profile()
                self.dsu_prof = p
                self._reset_gui()
                self._create_server_connection()

                self.new_dm_b.configure(state="normal")
            except Profile.DsuFileError:
                messagebox.showerror(
                    "DSU File Error",
                    "The file you chose either is not a .dsu file or does not exist.",
                )
            except Profile.DsuProfileError:
                messagebox.showerror(
                    "DSU File Format Error",
                    "The .dsu file you chose is not formatted correctly.",
                )
        self._disable_enable_menu_bar(False)

    def _add_dm_lb_options(self):
        self.dm_lb.delete(0, tkinter.END)
        for indx, recip in enumerate(self.dm_recipients):
            self.dm_lb.insert(indx + 1, recip)

    def _reset_gui(self):
        self.current_recipient = None
        self.dm_recipients = self.dsu_prof.get_recipients()
        self.new_message_field.config(state="disabled")
        self.send_message_b.config(state="disabled")
        self.conversation_text.configure(state="normal")
        self.conversation_text.delete(1.0, tkinter.END)
        self.conversation_text.configure(state="disabled")
        self._add_dm_lb_options()

    def _save_profile(self):
        dsu_path: pathlib.Path = pathlib.Path(self.dsu_prof.get_path())

        if not dsu_path.is_file():
            dsu_path.touch()

        try:
            self.dsu_prof.save_profile(self.dsu_prof.get_path())
        except Profile.DsuFileError:
            messagebox.showerror(
                "File Save Error",
                "An error occurred while attempting to save the file.",
            )

    def _send_message(self, recip: str):
        msg: str = self.new_message_field.get(1.0, tkinter.END)
        self.new_message_field.delete(1.0, tkinter.END)
        if self.ds_m and (msg and not msg.isspace()):
            try:
                if self.ds_m.send(msg, recip):
                    self.dsu_prof.add_direct_message(
                        recip, msg, str(time()), True
                    )
                    self._save_profile()
                    self._open_update_dm_chat(self.current_recipient, True)
                else:
                    messagebox.showerror(
                        "Message Send Error",
                        "An error ocurred when trying to send the message.",
                    )
            except SendRecvDataError:
                messagebox.showerror(
                    "Error Sending Message",
                    "There was a problem sending the message to the server.",
                )
        elif not self.ds_m:
            messagebox.showerror(
                "Error Sending Message",
                "A connection with the server has not been established.",
            )
        elif not (msg and not msg.isspace()):
            messagebox.showwarning(
                "Empty Message",
                "Messages that are empty or consist only of spaces cannot be sent.",
            )

    def _new_dm(self):
        add_new_dm = NewDMWindow()
        add_new_dm.transient(self)
        self._disable_enable_menu_bar(True)
        self.wait_window(add_new_dm)
        self._disable_enable_menu_bar(False)

        self.dsu_prof.new_dm(add_new_dm.new_dm_username)
        self._reset_gui()

    def _check_new_messages(self):
        if self.ds_m:
            try:
                new_msgs = self.ds_m.retrieve_new()
                if len(new_msgs) > 0:
                    for msg in new_msgs:
                        if not self.dsu_prof.check_dm_exists(msg.recipient):
                            self.dsu_prof.new_dm(msg.recipient)
                        self.dsu_prof.add_direct_message(
                            msg.recipient, msg.message, msg.timestamp, False
                        )
                    # self.dsu_prof.sort_direct_messages()
                    self.dm_recipients = self.dsu_prof.get_recipients()
                    self._save_profile()
            except SendRecvDataError:
                messagebox.showerror(
                    "Error Getting Message",
                    "There was a problem trying to retrieve new messages from the server.",
                )

    def _profile_settings(self):
        profile_settings = ProfileSettingsWindow()
        profile_settings.transient(self)
        self._disable_enable_menu_bar(True)
        self.wait_window(profile_settings)
        self._disable_enable_menu_bar(False)

        if profile_settings.new_dsuserver is not None:
            self.dsu_prof.change_dsuaddress(profile_settings.new_dsuserver)
        if profile_settings.new_username is not None:
            self.dsu_prof.change_username(profile_settings.new_username)
        if profile_settings.new_password is not None:
            self.dsu_prof.change_password(profile_settings.new_password)

        self._create_server_connection(settings_changed=True)

    def _reset_storage(self):
        try:
            all_msgs = self.ds_m.retrieve_all()
            self.dsu_prof.clear_direct_messages()
            for msg in all_msgs:
                if not self.dsu_prof.check_dm_exists(msg.recipient):
                    self.dsu_prof.new_dm(msg.recipient)
                self.dsu_prof.add_direct_message(
                    msg.recipient, msg.message, msg.timestamp, False
                )
            # self.dsu_prof.sort_direct_messages()
            self._reset_gui()
            self._save_profile()
        except SendRecvDataError:
            messagebox.showerror(
                "Error Getting Message",
                "There was a problem trying to retrieve new messages from the server.",
            )


class ProfileSettingsWindow(tkinter.Toplevel):
    def __init__(self):
        super().__init__()
        self.grab_set()
        self.focus_set()

        self.new_dsuserver = None
        self.new_username = None
        self.new_password = None

        self._draw()

    def _draw(self):
        self.resizable(0, 0)
        self.title("Profile Settings")
        self.grid_rowconfigure(0, weight=1)
        self.grid_columnconfigure(0, weight=1)

        new_dsuserver_var = tkinter.StringVar()
        new_username_var = tkinter.StringVar()
        new_password_var = tkinter.StringVar()

        content_frame = tkinter.Frame(self)
        content_frame.grid_rowconfigure(0, weight=1)
        content_frame.grid_rowconfigure(1, weight=1)
        content_frame.grid_rowconfigure(2, weight=1)
        content_frame.grid_columnconfigure(0, weight=1)
        content_frame.grid(row=0, column=0, sticky="nsew")

        new_dsuserver_frame = tkinter.Frame(content_frame)
        new_dsuserver_label = tkinter.Label(
            new_dsuserver_frame, text="DSU Server:"
        )
        new_dsuserver_field = tkinter.Entry(
            new_dsuserver_frame, textvariable=new_dsuserver_var
        )
        new_dsuserver_label.pack(side="left")
        new_dsuserver_field.pack(side="right")
        new_dsuserver_frame.grid(row=0, column=0, sticky="nsew")

        new_username_frame = tkinter.Frame(content_frame)
        new_username_label = tkinter.Label(
            new_username_frame, text="Username:"
        )
        new_username_field = tkinter.Entry(
            new_username_frame, textvariable=new_username_var
        )
        new_username_label.pack(side="left")
        new_username_field.pack(side="right")
        new_username_frame.grid(row=1, column=0, sticky="nsew")

        new_password_frame = tkinter.Frame(content_frame)
        new_password_label = tkinter.Label(
            new_password_frame, text="Password:"
        )
        new_password_field = tkinter.Entry(
            new_password_frame, textvariable=new_password_var
        )
        new_password_label.pack(side="left")
        new_password_field.pack(side="right")
        new_password_frame.grid(row=2, column=0, sticky="nsew")

        options_frame = tkinter.Frame(self)
        ok_button = tkinter.Button(
            options_frame,
            text="OK",
            command=lambda: self._ok_button(
                new_dsuserver_var.get(),
                new_username_var.get(),
                new_password_var.get(),
            ),
        )
        cancel_button = tkinter.Button(
            options_frame, text="Cancel", command=self.destroy
        )
        ok_button.pack(side="right")
        cancel_button.pack(side="right")
        options_frame.grid(row=1, column=0, sticky="nsew")

    def _ok_button(self, dsuserver, username, password):
        c_new_dsuserver_res = None
        c_new_username_res = None
        c_new_password_res = None

        if dsuserver:
            c_new_dsuserver_res: bool = _check_dsuserver(dsuserver)
        if username:
            c_new_username_res: bool = _check_username(username)
        if password:
            c_new_password_res: bool = _check_password(password)

        if (
            ((c_new_dsuserver_res is None) or c_new_dsuserver_res)
            and ((c_new_username_res is None) or c_new_username_res)
            and ((c_new_password_res is None) or c_new_password_res)
        ):
            if dsuserver:
                self.new_dsuserver = dsuserver
            if username:
                self.new_username = username
            if password:
                self.new_password = password
            self.destroy()
        else:
            messagebox.showerror(
                "Entry Error",
                "You either made an error in one of your entries or made no entry into any of the fields.",
            )


class NewDMWindow(tkinter.Toplevel):
    def __init__(self):
        super().__init__()
        self.grab_set()
        self.focus_set()

        self.new_dm_username: str = None

        self._draw()

    def _draw(self):
        self.resizable(0, 0)
        self.title("Start New DM")
        self.grid_rowconfigure(0, weight=1)
        self.grid_columnconfigure(0, weight=1)

        new_dm_username_var = tkinter.StringVar()

        content_frame = tkinter.Frame(self)
        content_frame.grid_rowconfigure(0, weight=1)
        content_frame.grid_rowconfigure(1, weight=1)
        content_frame.grid_columnconfigure(0, weight=1)
        content_frame.grid(row=0, column=0, sticky="nsew")

        new_dm_username_frame = tkinter.Frame(content_frame)
        new_dm_username_label = tkinter.Label(
            new_dm_username_frame, text="Username:"
        )
        new_dm_username_field = tkinter.Entry(
            new_dm_username_frame, textvariable=new_dm_username_var
        )
        new_dm_username_label.pack(side="left")
        new_dm_username_field.pack(side="right")
        new_dm_username_frame.grid(row=0, column=0, sticky="nsew")

        options_frame = tkinter.Frame(self)
        ok_button = tkinter.Button(
            options_frame,
            text="OK",
            command=lambda: self._ok_button(new_dm_username_var.get()),
        )
        cancel_button = tkinter.Button(
            options_frame, text="Cancel", command=self.destroy
        )
        ok_button.pack(side="right")
        cancel_button.pack(side="right")
        options_frame.grid(row=1, column=0, sticky="nsew")

    def _ok_button(self, new_dm_username: str):
        self.new_dm_username = new_dm_username
        self.destroy()


class NewProfileWindow(tkinter.Toplevel):
    def __init__(self):
        super().__init__()
        self.grab_set()
        self.focus_set()

        self.dsuserver = None
        self.username = None
        self.password = None
        self.path = None

        self._draw()

    def _draw(self):
        self.resizable(0, 0)
        self.title("Create New Profile")
        self.grid_rowconfigure(0, weight=1)
        self.grid_columnconfigure(0, weight=1)

        dsuserver_var = tkinter.StringVar()
        username_var = tkinter.StringVar()
        password_var = tkinter.StringVar()

        content_frame = tkinter.Frame(self)
        content_frame.grid_rowconfigure(0, weight=1)
        content_frame.grid_rowconfigure(1, weight=1)
        content_frame.grid_rowconfigure(2, weight=1)
        content_frame.grid_rowconfigure(3, weight=1)
        content_frame.grid_columnconfigure(0, weight=1)
        content_frame.grid(row=0, column=0, sticky="nsew")

        dsuserver_frame = tkinter.Frame(content_frame)
        dsuserver_label = tkinter.Label(dsuserver_frame, text="DSU Server:")
        dsuserver_field = tkinter.Entry(
            dsuserver_frame, textvariable=dsuserver_var
        )
        dsuserver_label.pack(side="left")
        dsuserver_field.pack(side="right")
        dsuserver_frame.grid(row=0, column=0, sticky="nsew")

        username_frame = tkinter.Frame(content_frame)
        username_label = tkinter.Label(username_frame, text="Username:")
        username_field = tkinter.Entry(
            username_frame, textvariable=username_var
        )
        username_label.pack(side="left")
        username_field.pack(side="right")
        username_frame.grid(row=1, column=0, sticky="nsew")

        password_frame = tkinter.Frame(content_frame)
        password_label = tkinter.Label(password_frame, text="Password:")
        password_field = tkinter.Entry(
            password_frame, textvariable=password_var
        )
        password_label.pack(side="left")
        password_field.pack(side="right")
        password_frame.grid(row=2, column=0, sticky="nsew")

        path_frame = tkinter.Frame(content_frame)
        path_label = tkinter.Label(path_frame, text="Path to folder:")
        path_field = tkinter.Button(
            path_frame, text="Choose Path...", command=self._get_set_directory
        )
        path_label.pack(side="left")
        path_field.pack(side="right")
        path_frame.grid(row=3, column=0, sticky="nsew")

        options_frame = tkinter.Frame(self)
        ok_button = tkinter.Button(
            options_frame,
            text="OK",
            command=lambda: self._ok_button(
                dsuserver_var.get(), username_var.get(), password_var.get()
            ),
        )
        cancel_button = tkinter.Button(
            options_frame, text="Cancel", command=self.destroy
        )
        ok_button.pack(side="right")
        cancel_button.pack(side="right")
        options_frame.grid(row=1, column=0, sticky="nsew")

    def _get_set_directory(self):
        self.path = tkinter.filedialog.askdirectory()

    def _ok_button(self, dsuserver, username, password):
        c_dsuserver_res: bool = _check_dsuserver(dsuserver)
        c_username_res: bool = _check_username(username)
        c_password_res: bool = _check_password(password)

        if (
            c_dsuserver_res
            and c_username_res
            and c_password_res
            and self.path
        ):
            self.dsuserver = dsuserver
            self.username = username
            self.password = password
            self.path = (
                str(pathlib.Path(self.path) / pathlib.Path(username)) + ".dsu"
            )
            self.destroy()
        else:
            c_dsuserver_res_msg = ""
            c_username_res_msg = ""
            c_password_res_msg = ""
            c_path_res_msg = ""
            if not c_dsuserver_res:
                c_dsuserver_res_msg = "DSU Server"
            if not c_username_res:
                c_username_res_msg = "Username"
            if not c_password_res:
                c_password_res_msg = "Password"
            if not self.path:
                c_path_res_msg = "Path to folder"
            messagebox.showerror(
                "Entry Error(s)",
                f"The following fields have an invalid entry:\n{c_dsuserver_res_msg}\n{c_username_res_msg}\n{c_password_res_msg}\n{c_path_res_msg}",
            )


def _check_dsuserver(dsuserver: str) -> bool:
    ipv4_address = dsuserver.split(".")
    if len(ipv4_address) != 4 or not all(
        [
            True if n.isdigit() and (0 <= int(n) <= 255) else False
            for n in ipv4_address
        ]
    ):
        return False
    return True


def _check_username(username: str) -> bool:
    if username and " " not in username:
        return True
    return False


def _check_password(password: str) -> bool:
    return _check_username(password)


if __name__ == "__main__":
    dsgui = DSGUI()
