import pygame
import random
import sys
import pygame_gui
import math

pygame.init()
pygame.display.init()

start_color = (255, 255, 0)
target_color = (255, 165, 0)


def show_game_over_screen():
    pygame.display.init()
    scrn = pygame.display.set_mode((600, 600))
    imp = pygame.image.load("mort.png").convert()
    scrn.blit(imp, (160, 200))
    pygame.display.flip()
    pygame.time.delay(2000)
    pygame.quit()
    sys.exit()


def you_won():
    pygame.display.init()
    scrn = pygame.display.set_mode((600, 600))
    imp = pygame.image.load("castig.png").convert()
    scrn.blit(imp, (160, 200))
    pygame.display.flip()
    pygame.time.delay(2000)
    pygame.quit()
    sys.exit()


def quit_game():
    pygame.quit()
    sys.exit()


screen_width = 606
screen_height = 606
screen = pygame.display.set_mode((screen_width, screen_height))
pygame.display.set_caption("PackMan")
clock = pygame.time.Clock()
white = (255, 255, 255)
black = (0, 0, 0)
yellow = (255, 255, 0)
gui_manager = pygame_gui.UIManager((screen_width, screen_height))
start_button = pygame_gui.elements.UIButton(
    relative_rect=pygame.Rect(
        (440, screen_height // 2 - 280), (150, 50)),
    text="Nivel 1",
    manager=gui_manager,
)
lvl_button = pygame_gui.elements.UIButton(
    relative_rect=pygame.Rect(
        (440, 290), (150, 50)),
    text="Nivel 2",
    manager=gui_manager,
)
last_button = pygame_gui.elements.UIButton(
    relative_rect=pygame.Rect(
        (440, 540), (150, 50)),
    text="Nivel 3",
    manager=gui_manager,
)


def get_interpolated_color(start_color, target_color, interpolation_factor):
    r = int((1 - interpolation_factor) *
            start_color[0] + interpolation_factor * target_color[0])
    g = int((1 - interpolation_factor) *
            start_color[1] + interpolation_factor * target_color[1])
    b = int((1 - interpolation_factor) *
            start_color[2] + interpolation_factor * target_color[2])
    return (r, g, b)


def draw_pacman(interpolation_factor):
    pacman_color = get_interpolated_color(
        start_color, target_color, interpolation_factor)
    radius = 20
    pacman_surface = pygame.Surface((radius * 2, radius * 2), pygame.SRCALPHA)
    pygame.draw.circle(pacman_surface, pacman_color, (radius, radius), radius)
    return pacman_surface


class Cookie(pygame.sprite.Sprite):
    def __init__(self, x, y):
        super().__init__()
        self.image = pygame.Surface((15, 15))
        self.image.fill((0, 255, 0))
        self.rect = self.image.get_rect()
        self.rect.x = x
        self.rect.y = y


class littleCookie(pygame.sprite.Sprite):
    def __init__(self, x, y):
        super().__init__()
        self.image = pygame.Surface((6, 6))
        self.image.fill((128, 128, 128))
        self.rect = self.image.get_rect()
        self.rect.x = x
        self.rect.y = y


def check_position(centerx, centery, direction, maze_walls, rad, pacman_speed):
    turns = [True, True, True, True]
    if direction == [0, 1]:
        aux_rect = pygame.Rect(centerx-rad, centery +
                               pacman_speed-rad, rad*2, rad*2)
        for wall in maze_walls:
            if aux_rect.colliderect(wall):
                turns[2] = False
    if direction == [1, 0]:
        aux_rect = pygame.Rect(centerx+pacman_speed-rad,
                               centery-rad, rad*2, rad*2)
        for wall in maze_walls:
            if aux_rect.colliderect(wall):
                turns[0] = False
    if direction == [-1, 0]:
        aux_rect = pygame.Rect(centerx-pacman_speed-rad,
                               centery-rad, rad*2, rad*2)
        for wall in maze_walls:
            if aux_rect.colliderect(wall):
                turns[1] = False
    if direction == [0, -1]:
        aux_rect = pygame.Rect(centerx-rad, centery -
                               pacman_speed-rad, rad*2, rad*2)
        for wall in maze_walls:
            if aux_rect.colliderect(wall):
                turns[3] = False
    return turns


def fulfill_map(X, Y, maze_walls, litte_cookie, marime_cookie):
    cookie_number = 0
    cookie_distance = 40
    nr_cookies_x = (X-cookie_distance) // cookie_distance
    nr_cookies_y = (Y-cookie_distance) // cookie_distance
    start_x = 37
    start_y = 37
    for i in range(nr_cookies_x):
        for j in range(nr_cookies_y):
            cook_x = (start_x + i * cookie_distance +
                      cookie_distance//2) % X
            cook_y = (start_y + j * cookie_distance +
                      cookie_distance//2) % Y
            cook_rect = pygame.Rect(
                cook_x, cook_y, marime_cookie, marime_cookie)
            if not any(cook_rect.colliderect(wall_rect) for wall_rect in maze_walls):
                cookies = littleCookie(cook_x, cook_y)
                litte_cookie.add(cookies)
                cookie_number += 1
    return cookie_number


class Ghost(pygame.sprite.Sprite):
    clock = pygame.time.Clock()

    def __init__(self, x, y, color):
        super().__init__()
        self.image = pygame.image.load("fantoma.png")
        self.rect = self.image.get_rect(center=(x, y))
        self.rect.x = x
        self.rect.y = y
        self.direction = random.choice([(0, -1), (0, 1), (-1, 0), (1, 0)])
        self.delay = 0

    def update(self, walls, player_rect):
        self.delay += 1
        if self.delay >= 3:
            new_rect = self.rect.move(self.direction)
            if new_rect.collidelist(walls) == -1:
                self.rect = new_rect
            else:
                choice = random.randint(0, 1)
                if choice == 0:
                    self.direction = random.choice(
                        [(0, -1), (0, 1), (-1, 0), (1, 0)])
                else:
                    self.direction = random.choice(
                        [(0, -2), (0, 2), (-2, 0), (2, 0)])
            if random.randint(0, 100) == 4:
                self.direction = random.choice(
                    [(0, -1), (0, 1), (-1, 0), (1, 0)])
            new_rect = self.rect.move(self.direction)
            self.delay = 0
        if self.rect.colliderect(player_rect):
            pygame.display.init()
            show_game_over_screen()


class CrazyGhost(pygame.sprite.Sprite):
    clock = pygame.time.Clock()

    def __init__(self, x, y, color):
        super().__init__()
        self.image = pygame.image.load("fantoma.png")
        self.rect = self.image.get_rect(center=(x, y))
        self.rect.x = x
        self.rect.y = y
        self.direction = random.choice([(0, -3), (0, 3), (-3, 0), (3, 0)])
        self.delay = 0

    def update(self, walls, player_rect):
        self.delay += 1
        if self.delay >= 3:
            new_rect = self.rect.move(self.direction)
            if new_rect.collidelist(walls) == -1:
                self.rect = new_rect
            else:
                choice = random.randint(0, 1)
                if choice == 0:

                    self.direction = random.choice(
                        [(0, -3), (0, 3), (-3, 0), (3, 0)])
                else:
                    self.direction = random.choice(
                        [(4, 0), (0, 4), (-4, 0), (4, 0)])
            if random.randint(0, 100) == 4:
                self.direction = random.choice(
                    [(0, -4), (0, 4), (-4, 0), (4, 0)])
            new_rect = self.rect.move(self.direction)
            self.delay = 0
        if self.rect.colliderect(player_rect):
            show_game_over_screen()
