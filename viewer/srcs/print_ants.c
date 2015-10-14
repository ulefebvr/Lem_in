int is_on_good_way(int node)
{
  t_ants *ants;

  ants = ft_global(NULL)->ants;
  while (ants)
  {
    if (ants->step == node)
      return (1);
    ants = ants->next;
  }
  return (0);
}

void  calc_ant(t_ants *ants)
{
  t_map *map;
  float x1;
  float x2;
  float y1;
  float y2;

  while (ants)
  {
    map = get_node_by_num(ants->start);
    x1 = (map->x * ft_global(NULL)->zoom);
    y1 = (map->y * ft_global(NULL)->zoom);
    map = get_node_by_num(ants->step);
    x2 = (map->x * ft_global(NULL)->zoom);
    y2 = (map->y * ft_global(NULL)->zoom);
    if (absi(x2 - x1) >= absi(y2 - y1))
      ants->longueur = absi(x2 -  x1);
    else
      ants->longueur = absi(y2 - x1);
    ants->dx = ((x2 - x1) / ants->longueur) * 5;
    ants->dy = ((y2 - y1) / ants->longueur) * 5;
    ants->x = x1 + 0.5;
    ants->y = y1 + 0.5;
    ants->i = 1;
    ants = ants->next;
  }
}

t_ants  *print_ant(t_ants *lista, int lap)
{
  t_ants *list;

  list = lista;
  sfRenderWindow_drawSprite((sfRenderWindow *)ft_global(NULL)->window, (sfSprite *)ft_global(NULL)->background, NULL);
  while (list && list->lap == lap)
  {
    if (list->i <= (list->longueur / 5))
    {
      get_event(ft_global(NULL)->window);
      ft_global(NULL)->sprite = (void *)sfSprite_create();
      sfSprite_setTexture((sfSprite *)ft_global(NULL)->sprite, ((int)list->i % 2) ? (sfTexture *)ft_global(NULL)->ant1 : (sfTexture *)ft_global(NULL)->ant2, sfTrue);
      sfSprite_move((sfSprite *)ft_global(NULL)->sprite, (sfVector2f){list->x - 9, list->y - 11});
      sfRenderWindow_drawSprite((sfRenderWindow *)ft_global(NULL)->window, (sfSprite *)ft_global(NULL)->sprite, NULL);
      sfSprite_destroy((sfSprite *)ft_global(NULL)->sprite);
    }
    list->x += list->dx;
    list->y += list->dy;
    list->i++;
    list = list->next;
  }
  sfRenderWindow_display((sfRenderWindow *)ft_global(NULL)->window);
  usleep(SPEED);
  return (lista->i < (lista->longueur / 5) ? lista : list);
}

void  print_them_all(t_ants *list)
{
  int lap;
  t_ants *tmp;

  lap = 0;
  calc_ant(list);
  tmp = list;
  while (tmp)
  {
    while ((tmp = print_ant(tmp, lap)) && tmp->lap == lap)
      ;
    lap++;
  }
}