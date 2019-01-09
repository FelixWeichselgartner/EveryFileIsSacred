import player
import FourWins

if __name__ == '__main__':
    yellowPlayer = player.player('yellow', 1)
    redPlayer = player.player('red', 0)
    game = FourWins.FourWins(yellowPlayer, redPlayer)
    winner = game.gameloop()
    if winner == 'n':
        print('there is no winner')
    else:
        print(f'the winner is {winner.getColor()}')

    if game.getTurn() == 1:
        print('the game had 1 turn')
    else:
        print(f'the game had {game.getTurn()} turns')