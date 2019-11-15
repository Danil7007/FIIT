import pygame
import random

YELLOW = (255, 255, 100)
BLUE = (50, 50, 255)
RED = (255, 50, 50)
BLACK = (0, 0, 0)
WHITE = (255,255,255)
SCREEN_WIDTH = 800
SCREEN_HEIGHT = 600
PADDLE_HEIGHT = 100
done = False

class Ball(pygame.sprite.Sprite):
    def __init__(self, x, y, xspeed, yspeed):
        super().__init__()
        self.image = pygame.Surface((16,16))
        self.rect = self.image.get_rect()
        self.x = x
        self.y = y
        self.rect.x = x
        self.rect.y = y
        pygame.draw.circle(self.image,YELLOW,(8,8),8)
        self.speed_x = xspeed
        self.speed_y = yspeed
        self.deathcount_left = None
        self.deathcount_right = None
        self.walls = None
        self.index = 0
    def checkdeath(self):
        if self.rect.x<0:
            self.deathcount_left.plus()
            self.rect.x = self.x
            self.rect.y = self.y
            self.speed_x = random.randint(8,12)
            self.speed_y = random.randint(8,12)
        elif self.rect.x>SCREEN_WIDTH:
            self.deathcount_right.plus()
            self.rect.x = self.x
            self.rect.y = self.y
            self.speed_x = random.randint(10,12)
            self.speed_y = random.randint(10,12)

    def update(self):
        self.checkdeath()
        self.rect.x += self.speed_x
        wall_hit_list = pygame.sprite.spritecollide(self, self.walls, False)
        if self.index == 1:
            self.rect.y+=self.speed_y
            self.index = 0
        else:
            if wall_hit_list:
                self.speed_x = -self.speed_x
                self.rect.y += self.speed_y
            else:
                self.rect.y += self.speed_y
                wall_hit_list = pygame.sprite.spritecollide(self, self.walls, False)
                if wall_hit_list:
                    self.speed_y = -self.speed_y
                    self.index=1


class Wall(pygame.sprite.Sprite):
    def __init__ (self, x, y, width, height):
        super().__init__()
        self.width = width
        self.height = height
        self.x = x
        self.y = y
        self.image = pygame.Surface([self.width, self.height])
        self.image.fill(BLUE)
        self.rect = self.image.get_rect()
        self.rect.x = x
        self.rect.y = y

class Paddle(Wall):
    def __init__ (self,x, y, width, height):
        super().__init__(x, y, width, height)
        self.walls = None
        self.speed = 0
        self.my_score = None
        self.my_enemy = None
    def changespeed(self, change):
        self.speed+=change
    def changelength(self):
        self.height = self.my_score.lengthcal(self.my_enemy)
        self.image = pygame.Surface([self.width, self.height])
        self.image.fill(BLUE)
        self.rect = self.image.get_rect()
        self.rect.x = self.x
        self.rect.y = self.y
    def update(self):
        self.y += self.speed
        self.changelength()
        wall_hit_list = pygame.sprite.spritecollide(self, self.walls, False)
        for wall in wall_hit_list:
            if self.speed>0:
                self.y = wall.rect.top - self.height
            else:
                self.y = wall.rect.bottom

class Score():
    def __init__(self, x, y,color):
        self.score = 0
        self.color = color
        self.x = x
        self.y = y
    def plus(self):
        self.score += 1
    def lengthcal(self, enemy):
        if self.score <= enemy.my_score.score:
            return PADDLE_HEIGHT
        else:
            return PADDLE_HEIGHT-(self.score-enemy.my_score.score)*10

    def draw(self):
        font = pygame.font.SysFont(None,32)
        self.image = font.render(str(self.score), True, self.color, BLACK)
        self.rect = self.image.get_rect()
        self.rect.x = self.x
        self.rect.y = self.y
        screen.blit(self.image, self.rect)

pygame.init()
screen = pygame.display.set_mode([SCREEN_WIDTH, SCREEN_HEIGHT])
pygame.display.set_caption('Pong')

all_sprite_list = pygame.sprite.Group()
all_wall_list = pygame.sprite.Group()
wall_list = pygame.sprite.Group()
empty_list = pygame.sprite.Group()

wall = Wall(0, 0, SCREEN_WIDTH, 10)
wall_list.add(wall)
all_wall_list.add(wall)
all_sprite_list.add(wall)
wall.walls = empty_list

wall = Wall(0, SCREEN_HEIGHT-10, SCREEN_WIDTH, 10)
wall_list.add(wall)
all_wall_list.add(wall)
all_sprite_list.add(wall)
wall.walls = empty_list

score_left = Score(190, 30, WHITE)
score_right = Score(590, 30, WHITE)

paddle_left = Paddle(50, 350, 10, PADDLE_HEIGHT)
paddle_right = Paddle(SCREEN_WIDTH-50, 350, 10, PADDLE_HEIGHT)

all_wall_list.add(paddle_left)
all_sprite_list.add(paddle_left)
paddle_left.my_score = score_right
paddle_left.my_enemy = paddle_right


all_wall_list.add(paddle_right)
all_sprite_list.add(paddle_right)
paddle_right.my_score = score_left
paddle_right.my_enemy = paddle_left

ball = Ball(400,300,14,9)
all_sprite_list.add(ball)

paddle_left.walls = wall_list
paddle_right.walls = wall_list
ball.walls = all_wall_list
ball.deathcount_left = score_left
ball.deathcount_right = score_right

while not done:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            done = True

        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_UP:
                paddle_right.changespeed(-8)
            elif event.key == pygame.K_DOWN:
                paddle_right.changespeed(8)
            elif event.key == pygame.K_w:
                paddle_left.changespeed(-8)
            elif event.key == pygame.K_s:
                paddle_left.changespeed(8)

        elif event.type == pygame.KEYUP:
            if event.key == pygame.K_UP:
                paddle_right.changespeed(8)
            elif event.key == pygame.K_DOWN:
                paddle_right.changespeed(-8)
            elif event.key == pygame.K_w:
                paddle_left.changespeed(8)
            elif event.key == pygame.K_s:
                paddle_left.changespeed(-8)

    all_sprite_list.update()
    if paddle_left.height<30 or paddle_right.height<30:
        break
    screen.fill(BLACK)
    score_left.draw()
    score_right.draw()
    all_sprite_list.draw(screen)
    pygame.display.flip()

pygame.quit()