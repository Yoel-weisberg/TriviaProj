class RoomData:
    def __init__(self, id, name, max_players, num_of_questions_in_game, time_per_question, is_active):
        self.id = id
        self.name = name
        self.max_players = max_players
        self.num_of_questions_in_game = num_of_questions_in_game
        self.time_per_question = time_per_question
        self.is_active = is_active
