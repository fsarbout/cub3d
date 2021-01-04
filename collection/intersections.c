/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsarbout <fsarbout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 23:39:30 by fsarbout          #+#    #+#             */
/*   Updated: 2021/01/04 11:32:59 by fsarbout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    horizontal_inter(float xstep, float ystep,  t_list **list)
{   
    g_dt.hhitdis = 0;
    g_dt.horwllhitx = 0;
    g_dt.horwllhity = 0;
    g_dt.horzhit = 0;
    g_dt.intery = (int)(g_dt.pos_y / TILE) * TILE;
    g_dt.intery += g_mv.raydown ? TILE : 0;
    g_dt.interx = g_dt.pos_x + (g_dt.intery - g_dt.pos_y) / tan(g_mv.rayangle);//
    ystep = TILE;
    ystep *= g_mv.rayup ? -1 : 1;
    xstep = ystep / tan(g_mv.rayangle);
    xstep *= (g_mv.rayleft && xstep > 0) ? -1 : 1;
    xstep *= (g_mv.rayright && xstep < 0) ? -1 : 1;
    g_dt.nxthorhitx = g_dt.interx;
    g_dt.nxthorhity = g_dt.intery;
    horizontal_loop(xstep, ystep, list);   
}

void    horizontal_loop(float xstep,float ystep,  t_list **list)
{    
    while (g_dt.nxthorhitx >= 0 && g_dt.nxthorhitx <= (g_dt.long_l * TILE)  
        && g_dt.nxthorhity >= 0 && g_dt.nxthorhity <= (g_dt.nbr_lines * TILE))
    {
        g_dt.checkx = g_dt.nxthorhitx;
        g_dt.checky = g_dt.nxthorhity + (g_mv.rayup ? -1 : 0 );

        if (hit_wall(g_dt.checkx, g_dt.checky ) == '2')
            sprite_calc_horz(list);
            //    g_dt.sp = 1;
        //  {   g_sp.x = g_dt.checkx;
        //          g_sp.y = g_dt.checky;}
  
        if (hit_wall(g_dt.checkx, g_dt.checky ) == '1')
        {
            g_dt.horzhit = 1;
            g_dt.horwllhitx = g_dt.nxthorhitx;
            g_dt.horwllhity = g_dt.nxthorhity;
            break;
        }
        else
        {
            g_dt.nxthorhitx +=  xstep;
            g_dt.nxthorhity +=  ystep;
        }
        
    }
}

void    vertical_inter(float xstep, float ystep,  t_list **list)
{
    g_dt.verwllhitx = 0;
    g_dt.verwllhity = 0;
    g_dt.vhitdis = 0;
    g_dt.verthit = 0;
    g_dt.interx = (int)(g_dt.pos_x / TILE) * TILE;
    g_dt.interx += g_mv.rayright ? TILE : 0;
    g_dt.intery = g_dt.pos_y + (g_dt.interx - g_dt.pos_x) * tan(g_mv.rayangle);
    xstep = TILE;
    xstep *= g_mv.rayleft ? -1 : 1;
    ystep = TILE * tan(g_mv.rayangle);
    ystep *= (g_mv.rayup && ystep > 0) ? -1 : 1;
    ystep *= (g_mv.raydown && ystep < 0) ? -1 : 1;
    g_dt.nxtvrthitx = g_dt.interx;
    g_dt.nxtvrthity = g_dt.intery;
    vertical_loop(xstep, ystep, list);
}

void    	vertical_loop(float xstep,float ystep,  t_list **list)
{
    
    while (g_dt.nxtvrthitx >= 0 && g_dt.nxtvrthitx <= (g_dt.long_l * TILE)  
        && g_dt.nxtvrthity >= 0 && g_dt.nxtvrthity <= (g_dt.nbr_lines * TILE))
    {
        g_dt.checkx = g_dt.nxtvrthitx + (g_mv.rayleft ? -1 :0);
        g_dt.checky = g_dt.nxtvrthity ;

        if (hit_wall(g_dt.checkx, g_dt.checky ) == '2')
            
          sprite_calc_vert(list);
        //   {  // g_dt.sp = 1;
        //       g_sp.x = g_dt.checkx;
        //          g_sp.y = g_dt.checky;
            
        //   }
        if (hit_wall(g_dt.checkx, g_dt.checky) == '1')
        {
            g_dt.verthit = 1;
            g_dt.verwllhitx = g_dt.nxtvrthitx;
            g_dt.verwllhity = g_dt.nxtvrthity;
            break;
        }
        else
        {
            g_dt.nxtvrthitx +=  xstep;
            g_dt.nxtvrthity +=  ystep;
        }
    }
}

void    sprite_calc_vert(t_list **list)
{
    //list = malloc(sizeof(t_list));
    t_sp sp;
    float angle;
        
    sp.x = g_dt.checkx;
    sp.y = g_dt.checky;
    sp.sp_verhitx = g_dt.nxtvrthitx;
    sp.sp_verhity = g_dt.nxtvrthity;
    sp.verthit = 1;
    sp.center = get_center_coor(sp.x, sp.y);
    sp.dist_plyr_sp = calculate_dist(sp.center.x, sp.center.y);
    angle = atan((sp.center.y - g_dt.pos_y ) / (sp.center.x - g_dt.pos_x));
    // normalize_angle(angle);
    // list->next = list;
    // printf("%f --- %f\n", list->sp.center.x ,list->sp.center.y); 
    /*if (list == NULL)
    {
        list = malloc(sizeof(t_list));
        list->sp = sp;
        list->next = NULL; 
    }
    else
    {
        
    }*/
   // printf("V %d  %d\n", sp.x / TILE, sp.y / TILE);
    lst_add_back(list, sp);
    
}

//need to normalize angle
void    sprite_calc_horz(t_list **list)
{
    t_sp sp;
    //sp = malloc(sizeof(t_sp));
    
    sp.x = g_dt.checkx;
    sp.y = g_dt.checky;
    sp.sp_horhitx = g_dt.nxthorhitx;
    sp.sp_horhity = g_dt.nxthorhity;
    sp.horzhit = 1;
    sp.center = get_center_coor(sp.x, sp.y);
    sp.dist_plyr_sp = calculate_dist(sp.center.x, sp.center.y);
    sp.angle = atan((sp.center.y - g_dt.pos_y ) / (sp.center.x - g_dt.pos_x));
    // list->next = list;
    printf("%f --- %f\n", sp.center.x ,sp.center.y);
    //printf("H %d  %d\n", sp.x / TILE, sp.y / TILE);

    lst_add_back(list, sp);
    //printf("%d\n", list->sp.x);
}
/// 