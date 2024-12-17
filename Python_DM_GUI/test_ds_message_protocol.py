import unittest
import ds_protocol as ds_p
from json import loads


class DSPTests(unittest.TestCase):
    def test_directmessage(self):
        answer1: dict = {
            "token": "user_token",
            "directmessage": {
                "entry": "Hello World!",
                "recipient": "ohhimark",
                "timestamp": "1603167689.3928561",
            },
        }
        test1: dict = loads(
            ds_p.DSPCommands.directmessage(
                "Hello World!", "ohhimark", "user_token"
            )
        )
        assert test1["token"] == answer1["token"]
        assert (
            test1["directmessage"]["entry"]
            == answer1["directmessage"]["entry"]
        )
        assert (
            test1["directmessage"]["recipient"]
            == answer1["directmessage"]["recipient"]
        )
        assert isinstance(test1["directmessage"]["timestamp"], str)

    def test_unreadmsgs(self):
        answer2: dict = {"token": "user_token", "directmessage": "new"}
        test2: dict = loads(ds_p.DSPCommands.unread_msgs("user_token"))
        assert test2["token"] == answer2["token"]
        assert test2["directmessage"] == answer2["directmessage"]

    def test_allmsgs(self):
        answer3: dict = {"token": "user_token", "directmessage": "all"}
        test3: dict = loads(ds_p.DSPCommands.all_msgs("user_token"))
        assert test3["token"] == answer3["token"]
        assert test3["directmessage"] == answer3["directmessage"]


if __name__ == "__main__":
    unittest.main()
