#include "viewer.h"

#include "SFML/Audio.h"
#include "SFML/Config.h"
#include "SFML/Network.h"
#include "SFML/OpenGL.h"
#include "SFML/System.h"
#include "SFML/Window.h"
#include <unistd.h>
#include "libft.h"

void ft_update_texture(sfRenderTexture *texture, sfRenderWindow *window)
{
  sfSprite* sprite;
  const sfTexture *f_texture;

  /* Update the texture */
  sprite = sfSprite_create();
  sfRenderTexture_display(texture);
  f_texture = sfRenderTexture_getTexture(texture);
  sfSprite_setTexture(sprite, f_texture, sfTrue);
  ft_global(NULL)->background = sprite;
  sfRenderWindow_drawSprite(window, sprite, NULL);
  sfRenderWindow_display(window);
  ft_global(NULL)->window = (void *)window;
  ft_global(NULL)->sprite = (void *)sprite;
  ft_global(NULL)->f_texture = (void *)f_texture;

}

void draw_background(sfRenderTexture **texture, sfRenderWindow *window, sfCircleShape **circle)
{
  t_links *save;
  t_map *map;

  map = ft_global(NULL);
  /* Clear the screen */
  sfRenderWindow_clear(window, MYBROWN);
  // Clear the texture
  sfRenderTexture_clear(*texture, MYBROWN);
  while (map)
  {
    if (map->links)
      save = map->links;
    while (save)
    {
      draw_line(map->num, save->node, *texture, MYGREY);
      save = save->next;
    }
    map = map->next;
  }
  map = ft_global(NULL);
  while (map)
  {
    sfCircleShape_setPosition(*circle, (sfVector2f){((map->x) * ft_global(NULL)->zoom) - ft_global(NULL)->node_size, ((map->y) * ft_global(NULL)->zoom) - ft_global(NULL)->node_size});
    if (map->start)
      sfCircleShape_setFillColor(*circle, MYGREEN);
    else if (map->end)
      sfCircleShape_setFillColor(*circle, MYBLUE);
    else
      sfCircleShape_setFillColor(*circle, MYGREY);
    if (is_on_good_way(map->num))
    {
      sfCircleShape_setOutlineThickness(*circle, 2.5);
      sfCircleShape_setOutlineColor(*circle, MYBLUE);
    }
    sfRenderTexture_drawCircleShape(*texture, *circle, NULL);
    map = map->next;
  }
}

int ft_init_window(sfRenderTexture **texture, sfCircleShape **circle)
{
  ft_global(NULL)->zoom = ft_global(NULL)->zoom ? ft_global(NULL)->zoom : ZOOM;
  ft_global(NULL)->node_size = ft_global(NULL)->zoom / 3 ? ft_global(NULL)->zoom / 3 : 1;
  if (!(sfRenderWindow *)ft_global(NULL)->window && !texture)
    return (0);
  *circle = sfCircleShape_create();
  sfCircleShape_setRadius(*circle, ft_global(NULL)->node_size);
  // Create the texture
  *texture = sfRenderTexture_create(WIDTH, HEIGHT, 64);
  return (1);
}

int ft_get_window(void)
{
  sfRenderTexture *texture;
  sfRenderWindow *window;
  sfCircleShape *circle;

  window = NULL;
  texture = NULL;
  circle = NULL;
  ft_init_window(&texture, &circle);
  window = (sfRenderWindow *)ft_global(NULL)->window;
  ft_global(NULL)->circle = (void *)circle;
  draw_background(&texture, window, &circle);
  ft_update_texture(texture, window);
  return (1);
}

int print_all(void)
{
      sfRenderWindow *window;
      sfVideoMode mode = {WIDTH, HEIGHT, 64};
      
      window = NULL;
      ft_global(NULL)->zoom = 0;
      /* Create the main window */
      ft_global(NULL)->window = (void *)sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
      ft_get_window();
      ft_set_perso();
      window = ft_global(NULL)->window;
      while (sfRenderWindow_isOpen(window))
      {
          print_them_all(ft_global(NULL)->ants);
          break;         
      }
      /* Cleanup resources */
      ft_free_struct(ft_global(NULL), window);

      return (1);
}