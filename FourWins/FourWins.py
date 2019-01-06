import player
import field
import os
import sys

clear = lambda: os.system("cls")

def interupt():
    input('press any button to continue')

class FourWins(object):
    board = [[field.field()] * 7 for c in range(7)]
    player1 = player.player('empty', 0)
    player2 = player.player('empty', 0)
    turn = 0

    def getTurn(self):
        return self.turn

    def __init__(self, p1, p2):
        self.player1 = p1
        self.player2 = p2

    def output(self):
        sys.stdout.write('  ')
        for p in range(0, 6):
            sys.stdout.write(str(p) + ' ')
        sys.stdout.write('\n')
        for i in range(0, 6):
            sys.stdout.write(str(i) + ' ')
            for k in range(0, 6):
                if self.board[i][k].getFigur() == 'red':
                    sys.stdout.write('R ')
                if self.board[i][k].getFigur() == 'yellow':
                    sys.stdout.write('Y ')
                if self.board[i][k].getFigur() == 'empty':
                    sys.stdout.write('░ ') #176
            sys.stdout.write('\n')

    def checkWinner(self):
        winner = 'n'
        for i in range(0, 3):
            for k in range(0, 6):
                if self.board[0 + i][k].getFigur() != 'empty':
                    if self.board[0 + i][k].getFigur() == self.board[1 + i][k].getFigur() == self.board[2 + i][k].getFigur() == self.board[3 + i][k].getFigur():
                        if self.board[0 + i][k].getFigur() == 'red':
                            winner = 'red'
                        elif self.board[0 + i][k].getFigur() == 'yellow':
                            winner = 'yellow'
        
        for i in range(0, 6):
            for k in range(0, 3):
                if self.board[i][0 + k].getFigur() != 'empty':
                    if self.board[i][0 + k].getFigur() == self.board[i][1 + k].getFigur() == self.board[i][2 + k].getFigur() == self.board[i][3 + k].getFigur():
                        if self.board[i][0 + k].getFigur() == 'red':
                            winner = 'red'
                        elif self.board[i][0 + k].getFigur() == 'yellow':
                            winner = 'yellow'
                    
        #diagonal to come
        return winner
    
    def canPlace(self, x, y):
        if not self.board[y][x].getFigur() == 'empty':
            return False
        if not y == 5:
            if self.board[y+1][x].getFigur() == 'empty':
                return False
        return True

    def place(self):
        x = int(input('x pos of your coin: '))
        y = int(input('y pos of your coin: '))

        if self.canPlace(x, y):
            if self.player1.isTurn(self.turn):
                self.board[y][x] = field.field(self.player1.getColor())
            elif self.player2.isTurn(self.turn):
                self.board[y][x] = field.field(self.player2.getColor())


    def gameloop(self):
        winner = 'n'
        while winner == 'n' and self.turn < 49:
            clear()
            self.output()
            self.place()
            winner = self.checkWinner()
            self.turn += 1

        self.output()
        if winner == self.player1.getColor():
            return self.player1
        elif winner == self.player2.getColor():
            return self.player2
        else:
            return 'n'