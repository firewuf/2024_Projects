import ds_client
import ds_protocol


class DirectMessage:
    def __init__(self, recipient, message, timestamp):
        self.recipient = recipient
        self.message = message
        self.timestamp = timestamp


class DirectMessenger:
    def __init__(self, dsuserver=None, username=None, password=None):
        self.token = None
        self.client = None
        self.dsuserver = dsuserver
        self.username = username
        self.password = password
        self.init_client()

    def _convert_to_dm(self, server_resp: ds_protocol.DataTuple) -> list:
        dms: list = []
        for msg in server_resp.message:
            dms.append(
                DirectMessage(msg["from"], msg["message"], msg["timestamp"])
            )
        return dms

    def send(self, message: str, recipient: str) -> bool:
        # must return true if message successfully sent, false if send failed.
        server_resp = ds_client.send_and_recieve(
            self.client,
            ds_protocol.DSPCommands.directmessage(
                message, recipient, self.token
            ),
        )
        return ds_protocol.check_ok(server_resp)

    def retrieve_new(self) -> list:
        # must return a list of DirectMessage objects containing all new messages
        server_resp = ds_client.send_and_recieve(
            self.client, ds_protocol.DSPCommands.unread_msgs(self.token)
        )
        return self._convert_to_dm(server_resp)

    def retrieve_all(self) -> list:
        # must return a list of DirectMessage objects containing all messages
        server_resp = ds_client.send_and_recieve(
            self.client, ds_protocol.DSPCommands.all_msgs(self.token)
        )
        return self._convert_to_dm(server_resp)

    def init_client(self, dsuserver=None):
        if dsuserver is not None:
            self.dsuserver = dsuserver
        self.client = ds_client.create_socket(self.dsuserver, 3021)
        server_resp = ds_client.send_and_recieve(
            self.client,
            ds_protocol.DSPCommands.join(self.username, self.password),
        )
        self.token = ds_protocol.get_token(server_resp)

    def close_client(self):
        self.client.close()
