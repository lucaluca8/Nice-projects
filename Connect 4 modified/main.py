import numpy as np
import pygame
import sys
import math
import random

#initializing player and AI turns
player=0
AI=1

# initialize used colors for the graphics
BLUE = (0, 0, 255)
BLACK = (0, 0, 0)
RED = (255, 0, 0)
YELLOW = (255, 255, 0)

# initialize size of the board
line_c = 6
col_c = 7

# initialize game check variable
game_over_check = False

# initializing the game graphics
pygame.init()

# set the number of pixels per square
squaresize = 100

# set the size on the screen
width = col_c * squaresize
height = (line_c + 1) * squaresize

# create the screen
size = (width, height)

# create the radius of the game circles
radius = int(squaresize / 2 - 5)

# variable to keep track of the current player turn
turn = 0



# function that creates the game board
def create_board():
    board = np.zeros((6, 7))
    return board


# initialize game board
board = create_board()

# function i use to drop a piece on the player chosen position
def drop_piece(color, col):
    line = 5
    ok = 0
    while ok == 0:
        if board[line][col] == 0:
            board[line][col] = color
            ok = 1  # exit while after the move is done
        else:
            line = line - 1

#set of functions to check for  win conditions
def check_for_win_horizontally(board,piece):
    for l in range(line_c):
        for c in range(col_c - 3):
            if (board[l][c] == piece and board[l][c + 1] == piece and board[l][c + 2] == piece and
                board[l][c + 3] == piece):
                return True
    return False
def check_for_win_vertically(board,piece):
    for l in range(line_c - 3):
        for c in range(col_c):
            if board[l][c] == piece and board[l + 1][c] == piece and board[l + 2][c] == piece and\
                board[l + 3][c] == piece:
                return True
    return False
def check_for_win_diagonally_ascending(board,piece):
    for l in range(line_c - 3):
        for c in range(col_c - 3):
            if board[l][c] == piece and board[l + 1][c + 1] == piece and board[l + 2][c + 2] == piece and\
                board[l + 3][c + 3] == piece:
                return True
    return False
def check_for_win_diagonally_descending(board,piece):
    for l in range(3, line_c):
        for c in range(col_c - 3):
            if board[l][c] == piece and board[l - 1][c + 1] == piece and board[l - 2][c + 2] == piece and\
                board[l - 3][c + 3] == piece:
                return True
    return False

# function to check if a player won
def is_win(board, piece):
    
# check horizontally
    if check_for_win_horizontally(board,piece) == True:
        return True
        
# check for win vertically
    if check_for_win_vertically(board,piece) == True:
        return True
        
# check for win diagonally ascending
    if check_for_win_diagonally_ascending(board,piece) == True:
        return True
    
#check for win diagonally descending
    if check_for_win_diagonally_descending(board,piece) == True:
        return True
    
    return False


# function to check if a column is full
def is_col_full(board, col):
    for l in range(6):
        if board[l][col] == 0:
            return False
    return True


# function that designs the board using pygame graphics stuff
def draw_board(board):
    for l in range(line_c):
        for c in range(col_c):
            pygame.draw.rect(screen, BLUE, (c * squaresize, l * squaresize + squaresize, squaresize, squaresize))
            if board[l][c] == 0:
                pygame.draw.circle(screen, BLACK,
                                   (c * squaresize + squaresize / 2, l * squaresize + squaresize + squaresize / 2),
                                   radius)
            elif board[l][c] == 1:
                pygame.draw.circle(screen, RED,
                                   (c * squaresize + squaresize / 2, l * squaresize + squaresize + squaresize / 2),
                                   radius)
            else:
                pygame.draw.circle(screen, YELLOW,
                                   (c * squaresize + squaresize / 2, l * squaresize + squaresize + squaresize / 2),
                                   radius)
    pygame.display.update()


# function to make the move of the current play
def player_move(piece):
    posx = event.pos[0]
    col = int(math.floor(posx / squaresize))
    
    if not is_col_full(board, col):
        drop_piece(piece, col)

#AI move using a random generated number to choose the collum
def AI_move_random(turn):
    col = random.randint(0,col_c-1)
    if turn == AI:
        if not is_col_full(board,col):
            pygame.time.wait(500)
            drop_piece(2,col)
 

#the board that the AI will use to make his decisions
AI_board= np.copy(board)

def move_chooser(board):
    AI_board=np.copy(board)


def AI_move_smart(turn,board):
    col = move_chooser(board)
    if turn == AI:
        if not is_col_full(board, col):
            pygame.time.wait(500)
            drop_piece(2, col)

# function that display the current player piece as the mouse is moving
def mouse_motion_display_function():
    pygame.draw.rect(screen, BLACK, (0, 0, width, squaresize))
    posx = event.pos[0]
    pygame.draw.circle(screen, RED, (posx, int(squaresize / 2)), radius)
    pygame.display.update()
   

# function that displays pieces that are dropped when the mouse is clicked
def mouse_button_press_display_function(turn):
    pygame.draw.rect(screen, BLACK, (0, 0, width, squaresize))
    if turn == player:
        player_move(1)
   

# function that swaps turn
def turn_swapper(turn):
    turn = (turn + 1) % 2
    return turn




# initialize the display of the created game board
screen = pygame.display.set_mode(size)
draw_board(board)
pygame.display.update()

# initialize the font of the game
font = pygame.font.SysFont("monospace", 75)

# game loop while game_over_check variable is false

while not game_over_check:
    
    for event in pygame.event.get():
        
        if event.type == pygame.QUIT:
            sys.exit()
        
        if event.type == pygame.MOUSEMOTION:
            mouse_motion_display_function()
        
        if event.type == pygame.MOUSEBUTTONDOWN:
            mouse_button_press_display_function(turn)
            
            if is_win(board, 1):
                label = font.render("Player " + str(1) + " won", 1, BLUE)
                screen.blit(label, (40, 10))
                game_over_check = True
            turn = turn_swapper(turn)
            
            draw_board(board)
            print(board)
    
    if turn == AI and not game_over_check:
       AI_move_smart(turn,board)
       draw_board(board)
       if is_win(board, 2):
        label = font.render("Player " + str(2) + " won", 1, BLUE)
        screen.blit(label, (40, 10))
        game_over_check = True
       turn = turn_swapper(turn)
       draw_board(board)
       print(board)
    
    
    if game_over_check:
        pygame.time.wait(3000)
