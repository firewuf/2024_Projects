import socket
import ds_protocol


class CreateSocketError(Exception):
    pass


class SendRecvDataError(Exception):
    pass


def send(
    server: str,
    port: int,
    username: str,
    password: str,
    message: str,
    bio: str = None,
):
    """
    The send function joins a ds server and sends a message, bio, or both

    :param server: The ip address for the ICS 32 DS server.
    :param port: The port where the ICS 32 DS server is accepting connections.
    :param username: The user name to be assigned to the message.
    :param password: The password associated with the username.
    :param message: The message to be sent to the server.
    :param bio: Optional, a bio for the user.
    """
    client: socket.socket = create_socket(server, port)
    if client is None:
        return False

    server_resp = send_and_recieve(
        client, ds_protocol.DSPCommands.join(username, password)
    )
    if not server_resp:
        print_stat_msg_and_close(
            "ERROR joining server.", client, server, port
        )
        return False
    token = ds_protocol.get_token(server_resp)

    if token:
        if message:
            server_resp = send_and_recieve(
                client, ds_protocol.DSPCommands.post(message, token)
            )
            if not server_resp:
                print_stat_msg_and_close(
                    "ERROR sending post to server.", client, server, port
                )
                return False

        if bio:
            server_resp = send_and_recieve(
                client, ds_protocol.DSPCommands.bio(bio, token)
            )
            if not server_resp:
                print_stat_msg_and_close(
                    "ERROR sending bio to server.", client, server, port
                )
                return False

        print_stat_msg_and_close(
            "Completed all operations successfully.", client, server, port
        )

        return True
    else:
        print_stat_msg_and_close(
            "ERROR: No token recieved.", client, server, port
        )
    return False


def create_socket(server: str, port: int) -> socket.socket:
    try:
        client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        # client.settimeout(5)
        client.connect((server, port))
        print(f"Connected to {server}:{port}")
        return client
    except Exception:
        print("Error creating socket connection to server.")
        raise CreateSocketError


def print_stat_msg_and_close(
    msg: str, client: socket, server: str, port: int
):
    client.close()
    print(msg)
    print(f"Successfully closed socket to {server}:{port}")


def send_and_recieve(client: socket.socket, action) -> ds_protocol.DataTuple:
    try:
        client.sendall(action.encode())
        server_resp: ds_protocol.DataTuple = ds_protocol.extract_json(
            recvall(client)
        )
        if ds_protocol.check_ok(server_resp):
            return server_resp
        else:
            print(server_resp.message)
            return None
    except Exception:
        print(
            "ERROR: An error occurred while trying to send or recieve data."
        )
        raise SendRecvDataError


def recvall(client: socket.socket):
    server_resps: list = []
    # try:
    server_resps.append(client.recv(4096))
    # while server_resp := client.recv(4096):
    #     server_resps.append(server_resp)
    # except TimeoutError:
    return (b"".join(server_resps)).decode()


if __name__ == "__main__":
    send(
        "168.235.86.101",
        3021,
        "kmrober2",
        "blaraubry324",
        "test post 32",
        "test bio 32",
    )
