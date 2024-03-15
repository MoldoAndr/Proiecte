import pygame
from auxiliar import*

def run_game_2():
    time = 0.0
    lab = [
        "###############",
        "#             #",
        "# ####   #### #",
        "#             #",
        "#  #       #  #",
        "#  #   #   #  #",
        "#      #      #",
        "# ###  #  ### #",
        "#             #",
        "# ###  #  ### #",
        "#             #",
        "#  #########  #",
        "#             #",
        "# #         # #",
        "###############"
    ]
    cell_size = 40
    maze_walls = []
    for row in range(len(lab)):
        for col in range(len(lab[row])):
            if lab[row][col] == '#':
                wall_x = col * cell_size
                wall_y = row * cell_size
                wall = pygame.Rect(wall_x, wall_y, cell_size, cell_size)
                maze_walls.append(wall)
    X = 600
    Y = 600
    scrn = pygame.display.set_mode((X, Y))
    pacman_radius = 19
    pacman_position = [300, 420]
    pacman_direction = [0, 0]
    score_font = pygame.font.Font(None, 36)
    score = 0
    scorebig = 0
    ghost_group = pygame.sprite.Group()
    fantoma_1 = Ghost(280, 80, (255, 0, 0))
    ghost_group.add(fantoma_1)
    fantoma_2 = Ghost(280, 80, (255, 0, 0))
    ghost_group.add(fantoma_2)
    fantoma_3 = Ghost(280, 80, (255, 0, 0))
    ghost_group.add(fantoma_3)
    fantoma_4 = Ghost(280, 80, (255, 0, 0))
    ghost_group.add(fantoma_4)
    marime_cookie = 15
    distanta_intre_cookies = 20
    num_cook_x = (
        screen_width - distanta_intre_cookies) // distanta_intre_cookies
    num_cook_y = (screen_height -
                  distanta_intre_cookies) // distanta_intre_cookies
    start_x = 37
    start_y = 37
    little_cookie_group = pygame.sprite.Group()
    cookies_number = fulfill_map(600,600,maze_walls,little_cookie_group,6)
    cookie_group = pygame.sprite.Group()
    for i in range(num_cook_x):
        for j in range(num_cook_y):
            cook_x = (start_x + i * distanta_intre_cookies +
                      distanta_intre_cookies//2) % 500
            cook_y = (start_y + j * distanta_intre_cookies +
                      distanta_intre_cookies//2) % 500
            cook_rect = pygame.Rect(
                cook_x, cook_y, marime_cookie, marime_cookie)
            if not any(wall_rect.colliderect(cook_rect) for wall_rect in maze_walls):
                if random.random() < 145:
                    cookies = Cookie(cook_x, cook_y)
                    cookie_group.add(cookies)
                    break
        running = True
        paused = False
        pacman_speed = 3
        random_color = (random.randint(0, 190)+60,
                        random.randint(0, 190)+60, random.randint(0, 190)+60)
        pacman_direction = [0,0]
        new_direction = [0,0]
        while running:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False
                    sys.exit()
                elif event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_SPACE:
                        paused = not paused
                    elif not paused:
                        if event.key == pygame.K_UP:
                                new_direction = [0, -1]
                        elif event.key == pygame.K_DOWN:
                                new_direction = [0,1]
                        elif event.key == pygame.K_LEFT:                               
                                new_direction = [-1,0]    
                        elif event.key == pygame.K_RIGHT: 
                                new_direction = [1, 0]

            if not paused:
                
                if check_position(pacman_position[0],pacman_position[1],new_direction,maze_walls,pacman_radius,pacman_speed)[0] == True and new_direction==[1,0] or check_position(pacman_position[0],pacman_position[1],new_direction,maze_walls,pacman_radius,pacman_speed)[1] == True and new_direction==[-1,0] or check_position(pacman_position[0],pacman_position[1],new_direction,maze_walls,pacman_radius,pacman_speed)[2] == True and new_direction==[0,1] or check_position(pacman_position[0],pacman_position[1],new_direction,maze_walls,pacman_radius,pacman_speed)[3] == True and new_direction==[0,-1]:  
                    if new_direction != [0,0]:
                        pacman_direction = new_direction 
                check = check_position(
                    pacman_position[0], pacman_position[1], pacman_direction, maze_walls, pacman_radius, pacman_speed)
                if pacman_direction == [1, 0] and check[0] == True:
                    pacman_position[0] += pacman_speed
                if pacman_direction == [-1, 0] and check[1] == True:
                    pacman_position[0] -= pacman_speed
                if pacman_direction == [0, -1] and check[3] == True:
                    pacman_position[1] -= pacman_speed
                if pacman_direction == [0, 1] and check[2] == True:
                    pacman_position[1] += pacman_speed
                pacman_rect = pygame.Rect(
                    pacman_position[0] - pacman_radius, pacman_position[1] - pacman_radius, pacman_radius * 2, pacman_radius * 2)
                for cookies in cookie_group:
                    if pacman_rect.colliderect(cookies.rect):
                        cookie_group.remove(cookies)
                        new_cookie = Cookie(random.randint(
                            210, 500), random.randint(210, 500))
                        while True:
                            if not any(new_cookie.rect.colliderect(wall) for wall in maze_walls):
                                if score < 1000:
                                    cookie_group.add(new_cookie)
                                    pygame.display.update()
                                    break
                                else:    
                                    break
                            else:
                                new_cookie = Cookie(random.randint(
                        
                                    0, 600), random.randint(0, 600))
                        if score < 1000:    
                            score += 100
                for littleC in little_cookie_group:
                    if pacman_rect.colliderect(littleC.rect):
                        little_cookie_group.remove(littleC)
                        scorebig += 10
                if score >= 1000 and scorebig == cookies_number* 10:
                    pygame.display.init()
                    next_lvl()
                for ghost in ghost_group:
                    ghost_group.update(maze_walls, pacman_rect)
            screen.fill(black)
            for wall in maze_walls:
                pygame.draw.rect(screen, random_color, wall)
            little_cookie_group.draw(screen)
            cookie_group.draw(screen)
            ghost_group.draw(screen)
            frequency = 5.0
            amplitude = 0.2
            interpolation_factor = (
                math.sin(time * frequency) * amplitude) + 0.5
            pacman_surface = draw_pacman(interpolation_factor)
            screen.blit(pacman_surface,
                        (pacman_position[0]-20, pacman_position[1]-20))
            paused_text = score_font.render(
                "Pauza: {}".format(paused), True, (0, 0, 0))
            screen.blit(paused_text, (440, 10))
            score_text = score_font.render(
                "Nivel 1 -> Scor: {}/{}".format(score+scorebig,1000+cookies_number*10), True, (0, 0, 0))
            screen.blit(score_text, (10, 10))
            pygame.display.update()
            time += clock.tick(60) / 1000.0
            pygame.display.flip()

        pygame.quit()


def next_lvl():
    time = 0.0
    lab = [
        "################",
        "#              #",
        "#      ##      #",
        "# ####    #### #",
        "#              #",
        "#  #        #  #",
        "#  #  ####  #  #",
        "#              #",
        "# ###  ##  ### #",
        "# #          # #",
        "# ###  ##  ### #",
        "#   #      #   #",
        "#  ##  ##  ##  #",
        "#   #      #   #",
        "#   #      #   #",
        "################"
    ]
    cell_size = 40
    maze_walls = []
    for row in range(len(lab)):
        for col in range(len(lab[row])):
            if lab[row][col] == '#':
                wall_x = col * cell_size
                wall_y = row * cell_size
                wall = pygame.Rect(wall_x, wall_y, cell_size, cell_size)
                maze_walls.append(wall)
    X = 640
    Y = 640
    scrn = pygame.display.set_mode((X, Y))
    pacman_radius = 19
    pacman_position = [260, 420]
    pacman_direction = [0, 0]
    score_font = pygame.font.Font(None, 36)
    score = 0
    scorebig = 0
    ghost_group = pygame.sprite.Group()
    fantoma_1 = Ghost(240, 80, (255, 0, 0))
    ghost_group.add(fantoma_1)
    fantoma_2 = Ghost(240, 80, (255, 0, 0))
    ghost_group.add(fantoma_2)
    fantoma_3 = Ghost(240, 80, (255, 0, 0))
    ghost_group.add(fantoma_3)
    fantoma_4 = Ghost(240, 80, (255, 0, 0))
    ghost_group.add(fantoma_4)
    marime_cookie = 15
    distanta_intre_cookies = 20
    num_cook_x = (
        screen_width - distanta_intre_cookies) // distanta_intre_cookies
    num_cook_y = (screen_height -
                  distanta_intre_cookies) // distanta_intre_cookies
    start_x = 37
    start_y = 37
    little_cookie_group = pygame.sprite.Group()
    cookies_number = fulfill_map(600,600,maze_walls,little_cookie_group,6)
    cookie_group = pygame.sprite.Group()
    for i in range(num_cook_x):
        for j in range(num_cook_y):
            cook_x = (start_x + i * distanta_intre_cookies +
                      distanta_intre_cookies//2) % 500
            cook_y = (start_y + j * distanta_intre_cookies +
                      distanta_intre_cookies//2) % 500
            cook_rect = pygame.Rect(
                cook_x, cook_y, marime_cookie, marime_cookie)
            if not any(wall_rect.colliderect(cook_rect) for wall_rect in maze_walls):
                if random.random() < 145:
                    cookies = Cookie(cook_x, cook_y)
                    cookie_group.add(cookies)
                    break
        running = True
        paused = False
        pacman_speed = 3
        random_color = (random.randint(0, 190)+60,
                        random.randint(0, 190)+60, random.randint(0, 190)+60)
        pacman_direction = [0,0]
        new_direction = [0,0]
        while running:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False
                    sys.exit()
                elif event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_SPACE:
                        paused = not paused
                    elif not paused:
                        if event.key == pygame.K_UP:
                                new_direction = [0, -1]
                        elif event.key == pygame.K_DOWN:
                                new_direction = [0,1]
                        elif event.key == pygame.K_LEFT:                               
                                new_direction = [-1,0]    
                        elif event.key == pygame.K_RIGHT: 
                                new_direction = [1, 0]

            if not paused:
                
                if check_position(pacman_position[0],pacman_position[1],new_direction,maze_walls,pacman_radius,pacman_speed)[0] == True and new_direction==[1,0] or check_position(pacman_position[0],pacman_position[1],new_direction,maze_walls,pacman_radius,pacman_speed)[1] == True and new_direction==[-1,0] or check_position(pacman_position[0],pacman_position[1],new_direction,maze_walls,pacman_radius,pacman_speed)[2] == True and new_direction==[0,1] or check_position(pacman_position[0],pacman_position[1],new_direction,maze_walls,pacman_radius,pacman_speed)[3] == True and new_direction==[0,-1]:  
                    if new_direction != [0,0]:
                        pacman_direction = new_direction 
                check = check_position(
                    pacman_position[0], pacman_position[1], pacman_direction, maze_walls, pacman_radius, pacman_speed)
                if pacman_direction == [1, 0] and check[0] == True:
                    pacman_position[0] += pacman_speed
                if pacman_direction == [-1, 0] and check[1] == True:
                    pacman_position[0] -= pacman_speed
                if pacman_direction == [0, -1] and check[3] == True:
                    pacman_position[1] -= pacman_speed
                if pacman_direction == [0, 1] and check[2] == True:
                    pacman_position[1] += pacman_speed
                pacman_rect = pygame.Rect(
                    pacman_position[0] - pacman_radius, pacman_position[1] - pacman_radius, pacman_radius * 2, pacman_radius * 2)
                for cookies in cookie_group:
                    if pacman_rect.colliderect(cookies.rect):
                        cookie_group.remove(cookies)
                        new_cookie = Cookie(random.randint(
                            210, 500), random.randint(210, 500))
                        while True:
                            if not any(new_cookie.rect.colliderect(wall) for wall in maze_walls):
                                if score < 1000:
                                    cookie_group.add(new_cookie)
                                    pygame.display.update()
                                    break
                                else:    
                                    break
                            else:
                                new_cookie = Cookie(random.randint(
                        
                                    0, 600), random.randint(0, 600))
                        if score < 1000:    
                            score += 100
                for littleC in little_cookie_group:
                    if pacman_rect.colliderect(littleC.rect):
                        little_cookie_group.remove(littleC)
                        scorebig += 10
                if score >= 1000 and scorebig == cookies_number* 10:
                    pygame.display.init()
                    last_lvl()
                for ghost in ghost_group:
                    ghost_group.update(maze_walls, pacman_rect)
            screen.fill(black)
            for wall in maze_walls:
                pygame.draw.rect(screen, random_color, wall)
            little_cookie_group.draw(screen)
            cookie_group.draw(screen)
            ghost_group.draw(screen)
            frequency = 5.0
            amplitude = 0.2
            interpolation_factor = (
                math.sin(time * frequency) * amplitude) + 0.5
            pacman_surface = draw_pacman(interpolation_factor)
            screen.blit(pacman_surface,
                        (pacman_position[0]-20, pacman_position[1]-20))
            paused_text = score_font.render(
                "Pauza: {}".format(paused), True, (0, 0, 0))
            screen.blit(paused_text, (440, 10))
            score_text = score_font.render(
                "Nivel 2 -> Scor: {}/{}".format(score+scorebig,1000+cookies_number*10), True, (0, 0, 0))
            screen.blit(score_text, (10, 10))
            pygame.display.update()
            time += clock.tick(60) / 1000.0
            pygame.display.flip()

        pygame.quit()




def last_lvl():
    time = 0.0
    lab = [
        "##################",
        "#                #",
        "# # ##  ##  ## # #",
        "#       ##       #",
        "# ##          ## #",
        "# ## #  ##  # ## #",
        "#      ####      #",
        "#                #",
        "# ### ###### ### #",
        "#  #          #  #",
        "# ###   ##   ### #",
        "#                #",
        "#  ## ##  ## ##  #",
        "#      #  #      #",
        "#  ###      ###  #",
        "#      ####      #",
        "# #            # #",
        "###################"
    ]
    cell_size = 40
    maze_walls = []
    for row in range(len(lab)):
        for col in range(len(lab[row])):
            if lab[row][col] == '#':
                wall_x = col * cell_size
                wall_y = row * cell_size
                wall = pygame.Rect(wall_x, wall_y, cell_size, cell_size)
                maze_walls.append(wall)
    X = 720
    Y = 720
    scrn = pygame.display.set_mode((X, Y))
    pacman_radius = 19
    pacman_position = [260, 389]
    pacman_direction = [0, 0]
    score_font = pygame.font.Font(None, 36)
    score = 0
    scorebig = 0
    ghost_group = pygame.sprite.Group()
    fantoma_1 = Ghost(280, 80, (255, 0, 0))
    ghost_group.add(fantoma_1)
    fantoma_2 = Ghost(280, 80, (255, 0, 0))
    ghost_group.add(fantoma_2)
    fantoma_3 = Ghost(280, 80, (255, 0, 0))
    ghost_group.add(fantoma_3)
    fantoma_4 = Ghost(280, 80, (255, 0, 0))
    ghost_group.add(fantoma_4)
    ghost_group_2 = pygame.sprite.Group()
    nebunul = CrazyGhost(280, 80, (255, 255, 255))
    ghost_group_2.add(nebunul)
    marime_cookie = 15
    distanta_intre_cookies = 2
    start_x = 37
    start_y = 37
    little_cookie_group = pygame.sprite.Group()
    cookies_number = fulfill_map(720,720,maze_walls,little_cookie_group,6)
    cookie_group = pygame.sprite.Group()
    while True:
            cook_rect = pygame.Rect(
                random.randint(0,720), random.randint(0,720), marime_cookie, marime_cookie)
            if not any(cook_rect.colliderect(wall_rect) for wall_rect in maze_walls):
                cookies = Cookie(cook_rect.x,cook_rect.y )
                cookie_group.add(cookies)
                break
            else:
                cook_rect = pygame.Rect(
                random.randint(0,720), random.randint(0,720), marime_cookie, marime_cookie)
    running = True
    paused = False
    pacman_speed = 3
    random_color = (random.randint(0, 190)+60,
                    random.randint(0, 190)+60, random.randint(0, 190)+60)
    new_direction = [0, 0] 
    pacman_direction = [0 ,0]
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
                sys.exit()
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_SPACE:
                    paused = not paused
                elif not paused:
                    if event.key == pygame.K_1:
                        pacman_speed = 3
                    elif event.key == pygame.K_2:
                        pacman_speed = 4
                    elif event.key == pygame.K_3:
                        pacman_speed = 6
                    if event.key == pygame.K_UP :
                        new_direction = [0, -1]
                    elif event.key == pygame.K_DOWN:
                        new_direction = [0, 1]
                    elif event.key == pygame.K_LEFT :
                        new_direction = [-1, 0]
                    elif event.key == pygame.K_RIGHT: 
                        new_direction = [1, 0]

        if not paused:
            
            if check_position(pacman_position[0],pacman_position[1],new_direction,maze_walls,pacman_radius,pacman_speed)[0] == True and new_direction==[1,0] or check_position(pacman_position[0],pacman_position[1],new_direction,maze_walls,pacman_radius,pacman_speed)[1] == True and new_direction==[-1,0] or check_position(pacman_position[0],pacman_position[1],new_direction,maze_walls,pacman_radius,pacman_speed)[2] == True and new_direction==[0,1] or check_position(pacman_position[0],pacman_position[1],new_direction,maze_walls,pacman_radius,pacman_speed)[3] == True and new_direction==[0,-1]:  
                if new_direction != [0,0]:
                    pacman_direction = new_direction 
            check = check_position(
                pacman_position[0], pacman_position[1], pacman_direction, maze_walls, pacman_radius, pacman_speed)
            if pacman_direction == [1, 0] and check[0] == True:
                pacman_position[0] += pacman_speed
            if pacman_direction == [-1, 0] and check[1] == True:
                pacman_position[0] -= pacman_speed
            if pacman_direction == [0, -1] and check[3] == True:
                pacman_position[1] -= pacman_speed
            if pacman_direction == [0, 1] and check[2] == True:
                pacman_position[1] += pacman_speed
            pacman_rect = pygame.Rect(
                pacman_position[0] - pacman_radius, pacman_position[1] - pacman_radius, pacman_radius * 2, pacman_radius * 2)
            for cookies in cookie_group:
                if pacman_rect.colliderect(cookies.rect):
                    cookie_group.remove(cookies)
                    new_cookie = Cookie(random.randint(
                       0,720), random.randint(0,720))
                    while True:
                        if not any(new_cookie.rect.colliderect(wall) for wall in maze_walls):
                            if score < 1000:
                                cookie_group.add(new_cookie)
                                pygame.display.update()
                                break
                            else:    
                                break
                        else:
                            new_cookie = Cookie(random.randint(
                                0, 720), random.randint(0, 720))
                    if score < 1000:    
                        score += 100
            for littleC in little_cookie_group:
                if pacman_rect.colliderect(littleC.rect):
                    little_cookie_group.remove(littleC)
                    scorebig += 10
            if score >= 1000 and scorebig == cookies_number* 10:
                pygame.display.init()
                next_lvl()
            for ghost in ghost_group:
                ghost_group.update(maze_walls, pacman_rect)
                ghost_group_2.update(maze_walls,pacman_rect)
            
        screen.fill(black)
        for wall in maze_walls:
            pygame.draw.rect(screen, random_color, wall)
        little_cookie_group.draw(screen)
        cookie_group.draw(screen)
        ghost_group.draw(screen)
        ghost_group_2.draw(screen)
        frequency = 5.0
        amplitude = 0.2
        interpolation_factor = (
            math.sin(time * frequency) * amplitude) + 0.5
        pacman_surface = draw_pacman(interpolation_factor)
        screen.blit(pacman_surface,
                    (pacman_position[0]-20, pacman_position[1]-20))
        speed_text = score_font.render(
            "Apasa 1, 2 sau 3 pentru diferite viteze", True, (0, 0, 0))
        paused_text = score_font.render(
            "Pauza: {}".format(paused), True, (0, 0, 0))
        score_text = score_font.render(
            "Nivel 3 -> Scor: {}/{}".format(score+scorebig,1000+cookies_number*10), True, (0, 0, 0))
        screen.blit(paused_text, (540, 10))
        screen.blit(speed_text, (240, 690))
        screen.blit(score_text, (10, 10))
        pygame.display.update()
        time += clock.tick(60) / 1000.0
        pygame.display.flip()
    pygame.quit()
    sys.exit()