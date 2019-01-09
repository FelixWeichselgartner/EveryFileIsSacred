class player(object):
    color = ''
    turnnumber = 0

    def __init__(self, clr, turnn):
        self.color = clr
        self.turnnumber = turnn

    def getColor(self):
        return self.color

    def isTurn(self, turn):
        if turn % 2 == self.turnnumber:
            return True
        else:
            return False