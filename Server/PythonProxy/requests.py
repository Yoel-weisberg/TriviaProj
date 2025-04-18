from getMesseges import *


class LoginRequest:
    def __init__(self, user_name, password):
        self.user_name = user_name
        self.password = password

    def getMessage(self):
        data = {"username": self.user_name, "password": self.password}
        return parseRequestToMessage(data, LOGIN)


class SignUpRequest:
    def __init__(self, user_name, password, email, address, phone_number, birth_date):
        self.user_name = user_name
        self.password = password
        self.email = email
        self.address = address
        self.phone_number = phone_number
        self.birth_date = birth_date

    def getMessage(self):
        data = {
            "username": self.user_name,
            "password": self.password,
            "email": self.email,
            "address": self.address,
            "phone_number": self.phone_number,
            "birth_date": self.birth_date
        }
        return parseRequestToMessage(data, SIGN_UP)


# Similar implementation for the other classes
class GetPlayersInRoomRequest:
    def __init__(self, room_id):
        self.room_id = room_id

    def getMessage(self):
        data = {"room_id": self.room_id}
        return parseRequestToMessage(data, GET_PLAYERS_REQ)


class JoinRoomRequest:
    def __init__(self, room_id):
        self.room_id = room_id

    def getMessage(self):
        data = {"room_id": self.room_id}
        return parseRequestToMessage(data, JOIN_ROOM_REQ)


class CreateRoomRequest:
    def __init__(self, room_name, max_users, question_count, answer_timeout):
        self.room_name = room_name
        self.max_users = max_users
        self.question_count = question_count
        self.answer_timeout = answer_timeout

    def getMessage(self):
        data = {
            "room_name": self.room_name,
            "max_users": self.max_users,
            "question_count": self.question_count,
            "answer_timeout": self.answer_timeout
        }
        return parseRequestToMessage(data, CREATE_ROOM_REQ)


class HighScoreRequest:
    def getMessage(self):
        data = {}
        return parseRequestToMessage(data, GET_HIGH_SCORE_REQ)

class personalStatsRequest:
    def getMessage(self):
        data = {}
        return parseRequestToMessage(data, GET_PERSONAL_STATS_REQ)


class LogoutRequest:
    def getMessage(self):
        data = {}
        return parseRequestToMessage(data, LOGOUT_REQ)


class GetRoomRequest:
    def getMessage(self):
        data = {}
        return parseRequestToMessage(data, GET_ROOM_REQ)
