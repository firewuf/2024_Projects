import json
from time import time
from collections import namedtuple


DataTuple = namedtuple(
    "DataTuple", ["type", "message", "token"], defaults=(None)
)


class DSPCommands:
    def join(usr: str, pwd: str):
        join_json: dict = {
            "join": {"username": usr, "password": pwd, "token": ""}
        }
        return json.dumps(join_json)

    def post(entry: str, token: str):
        post_json: dict = {
            "token": token,
            "post": {"entry": entry, "timestamp": str(time())},
        }
        return json.dumps(post_json)

    def bio(entry: str, token: str):
        bio_json: dict = {
            "token": token,
            "bio": {"entry": entry, "timestamp": str(time())},
        }
        return json.dumps(bio_json)

    def directmessage(entry: str, recipient: str, token: str):
        dm: dict = {
            "token": token,
            "directmessage": {
                "entry": entry,
                "recipient": recipient,
                "timestamp": str(time()),
            },
        }
        return json.dumps(dm)

    def unread_msgs(token: str):
        unrd_msgs: dict = {"token": token, "directmessage": "new"}
        return json.dumps(unrd_msgs)

    def all_msgs(token: str):
        a_msgs: dict = {"token": token, "directmessage": "all"}
        return json.dumps(a_msgs)

    def recv(msg):
        ok_json = json.loads(msg)
        return ok_json


def extract_json(json_msg: str) -> DataTuple:
    """
    Call the json.loads function on a json string and
    convert it to a DataTuple object

    TODO: replace the pseudo placeholder keys with actual DSP protocol keys
    """
    try:
        json_msg = json_msg.strip("\r\n")
        json_obj = json.loads(json_msg)
        resp_type = json_obj["response"]["type"]
        if resp_type == "ok" and "token" in json_obj["response"].keys():
            resp_token = json_obj["response"]["token"]
        else:
            resp_token = None

        if resp_type == "ok" and "messages" in json_obj["response"].keys():
            resp_message = json_obj["response"]["messages"]
        elif resp_type == "ok" and "message" in json_obj["response"].keys():
            resp_message = json_obj["response"]["message"]

    except (json.JSONDecodeError, KeyError):
        print("Json cannot be decoded.")

    return DataTuple(resp_type, resp_message, resp_token)


def check_ok(server_resp: DataTuple) -> bool:
    if server_resp.type == "ok":
        return True
    return False


def get_token(server_resp: DataTuple) -> str:
    return server_resp.token
