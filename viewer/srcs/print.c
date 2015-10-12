#include "viewer.h"
#include "SFML/Audio.h"
#include "SFML/Config.h"
#include "SFML/Graphics.h"
#include "SFML/Network.h"
#include "SFML/OpenGL.h"
#include "SFML/System.h"
#include "SFML/Window.h"
#include <unistd.h>

#include "libft.h"

#include <stdio.h>

t_map *get_node_by_num(int num)
{
  t_map *begin;

  begin = ft_global(NULL);
  while (begin->num != num)
    begin = begin->next;
  return (begin);
}

float absi(float i)
{
  if (i < 0)
    return (-i);
  return (i);
}

void move_ant(sfRenderWindow **window, sfSprite *sprite, const sfTexture **f_texture, int node_a, int node_b)
{
  t_map *map;
  float x, y, x1, x2, y1, y2, dx, dy, i;
  float longueur;

  longueur = 0;
  map = get_node_by_num(node_a);
  x1 = (map->x * ZOOM);
  y1 = (map->y * ZOOM);
  map = get_node_by_num(node_b);
  x2 = (map->x * ZOOM);
  y2 = (map->y * ZOOM);

  if (absi(x2 - x1) >= absi(y2 - y1))
    longueur = absi(x2 -  x1);
  else
    longueur = absi(y2 - x1);
  dx = ((x2 - x1) / longueur) * 5;
  dy = ((y2 - y1) / longueur) * 5;
  x = x1 + 0.5;
  y = y1 + 0.5;
  i = 1;
  while (i <= (longueur / 5))
  {
    sfRenderWindow_drawSprite(*window, ft_global(NULL)->background, NULL);
    sprite = sfSprite_create();
    sfSprite_setTexture(sprite, *f_texture, sfTrue);
    *f_texture = sfTexture_createFromFile((int)i % 2 ? "ressources/img/mario1.png" : "ressources/img/mario2.png", NULL);
    sfSprite_move(sprite, (sfVector2f){x - 16, y - 50});
    sfRenderWindow_drawSprite(*window, sprite, NULL);
    sfSprite_destroy(sprite);
    sfRenderWindow_display(*window);
    // usleep(SPEED);
    x = x + dx;
    y = y + dy;
    i++;  }
}

void draw_line(int node_a, int node_b, sfRenderTexture *texture)
{
  t_map *map;
  sfVertexArray *vertex;
  sfVertex      vert;
  float x, y, x1, x2, y1, y2, dx, dy, i;
  float longueur;

  longueur = 0;
  vertex = sfVertexArray_create();
  map = get_node_by_num(node_a);
  x1 = (map->x * ZOOM);
  y1 = (map->y * ZOOM);
  map = get_node_by_num(node_b);
  x2 = (map->x * ZOOM);
  y2 = (map->y * ZOOM);

  if (absi(x2 - x1) >= absi(y2 - y1))
    longueur = absi(x2 -  x1);
  else
    longueur = absi(y2 - x1);
  dx = (x2 - x1) / longueur;
  dy = (y2 - y1) / longueur;
  x = x1 + 0.5;
  y = y1 + 0.5;
  i = 1;
  while (i <= longueur)
  {
    vert.position = (sfVector2f){x, y};
    vert.color = (sfColor){150, 150, 150, 100};
    // vert.texCoords = (sfVector2f){x, y};
    sfVertexArray_append(vertex, vert);
    x = x + dx;
    y = y + dy;
    i++;
  }
  sfRenderTexture_drawVertexArray(texture, vertex, NULL);
}

int test_csfml(void)
{
      sfVideoMode mode = {WIDTH, HEIGHT, 64};
      sfRenderWindow* window;
      sfRenderWindow* window_save;
      sfEvent event;
      sfCircleShape *circle;
      t_map *map;
      t_ants *ants;
      t_links *save;
      sfRenderTexture *texture;
      const sfTexture *f_texture;
      sfSprite* sprite;

      map = ft_global(NULL);
      circle = sfCircleShape_create();
      sfCircleShape_setRadius(circle, NODE_SIZE);
      
      int i = 0;

      /* Create the main window */
      window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
      // Create the texture
      texture = sfRenderTexture_create(WIDTH, HEIGHT, 64);
      if (!window && !texture)
          return (0);
  
          /* Clear the screen */
          sfRenderWindow_clear(window, sfBlack);
          // Clear the texture
          sfRenderTexture_clear(texture, sfBlack);
          while (map)
          {
            if (map->links)
              save = map->links;
            while (save)
            {
              draw_line(map->num, save->node, texture);
              save = save->next;
            }
            map = map->next;
          }
          map = ft_global(NULL);
          while (map)
          {
            sfCircleShape_setPosition(circle, (sfVector2f){((map->x) * ZOOM) - NODE_SIZE, ((map->y) * ZOOM) - NODE_SIZE});
            if (map->start)
              sfCircleShape_setFillColor(circle, (sfColor){189, 181, 9, 255});
            else if (map->end)
              sfCircleShape_setFillColor(circle, (sfColor){9, 189, 89, 255});
            else
              sfCircleShape_setFillColor(circle, (sfColor){9, 157, 179, 255});
            sfRenderTexture_drawCircleShape(texture, circle, NULL);
            map = map->next;
          }
      /* Update the texture */

      sprite = sfSprite_create();
      sfRenderTexture_display(texture);
      f_texture = sfRenderTexture_getTexture(texture);
      sfSprite_setTexture(sprite, f_texture, sfTrue);
      ft_global(NULL)->background = sprite;
      sfRenderWindow_drawSprite(window, sprite, NULL);
      sfRenderWindow_display(window);
      while (sfRenderWindow_isOpen(window))
      {
          /* Process events */
          if (sfRenderWindow_pollEvent(window, &event))
          {
              /* Close window : exit */
              if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
              else if ((event.type == sfEvtKeyPressed) && (event.key.code == sfKeyEscape))
                sfRenderWindow_close(window);
          }
          ants = ft_global(NULL)->ants;
          while (ants)
          {
            move_ant(&window, sprite, &f_texture, ants->start, ants->step);
            ants = ants->next;
          }
          break;         
      }
      sfCircleShape_destroy(circle);

      /* Cleanup resources */
      sfRenderWindow_destroy(window);
  
      return (1);
}