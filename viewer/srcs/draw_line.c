float absi(float i)
{
  if (i < 0)
    return (-i);
  return (i);
}

void draw_line(int node_a, int node_b, sfRenderTexture *texture, sfColor color)
{
  t_map *map;
  sfVertexArray *vertex;
  sfVertex      vert;
  float x, y, x1, x2, y1, y2, dx, dy, i;
  float longueur;

  longueur = 0;
  vertex = sfVertexArray_create();
  map = get_node_by_num(node_a);
  x1 = (map->x * ft_global(NULL)->zoom);
  y1 = (map->y * ft_global(NULL)->zoom);
  map = get_node_by_num(node_b);
  x2 = (map->x * ft_global(NULL)->zoom);
  y2 = (map->y * ft_global(NULL)->zoom);

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
    vert.color = color;
    // vert.texCoords = (sfVector2f){x, y};
    sfVertexArray_append(vertex, vert);
    x = x + dx;
    y = y + dy;
    i++;
  }
  sfRenderTexture_drawVertexArray(texture, vertex, NULL);
  sfVertexArray_destroy(vertex);
}