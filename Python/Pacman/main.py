import pygame
import pygame_gui
import sys
from levels import *
from auxiliar import *  

def start_game():
    pygame.display.init() 
    run_game_2()

def menu():
    pygame.mixer.init()
    pygame.mixer.music.load("music.mp3")
    pygame.mixer.music.set_volume(0.8)
    pygame.mixer.music.play(-1)
    is_running = True   
    X = 600 
    Y = 600
    pygame.display.init()
    scrn = pygame.display.set_mode((X, Y))
    pygame.display.set_caption('Packman')
    imp = pygame.image.load("back.png").convert()
    scrn.blit(imp, (0, 0))
    pygame.display.flip()

    while is_running:
        time_delta = clock.tick(60) / 1000
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                is_running = False
            elif event.type == pygame_gui.UI_BUTTON_PRESSED:
                if event.ui_element == start_button:
                    start_game()
                elif event.ui_element == lvl_button:
                    next_lvl()
                elif event.ui_element == last_button:
                    last_lvl()

            gui_manager.process_events(event)
        gui_manager.update(time_delta)
        gui_manager.draw_ui(screen)
        pygame.display.update()
    pygame.quit()

pygame.display.init()
menu()
