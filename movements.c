/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_shit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 21:36:24 by kblack            #+#    #+#             */
/*   Updated: 2019/09/02 21:36:30 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void mtx_multi(float mtx1[4][4], float mtx2[4][4], float dst[4][4])
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < 4)
    {
        while (j < 4)
        {
            dst[i][j] = mtx1[i][0]*mtx2[0][j]+
                        mtx1[i][1]*mtx2[1][j]+
                        mtx1[i][2]*mtx2[2][j]+
                        mtx1[i][3]*mtx2[3][j]
        }
    }
}

void mtx_copy(float src[4][4], float dst[4][4])
{
    int i;
    int j;

    while (i < 4)
    {
        while (j < 4)
        {
            dst[i][j] = src[i][j];
        }
    }
}

void identity_mtx(float mtx[4][4])
{
    mtx[0][0] = 1; mtx[0][1] = 0; mtx[0][2] = 0; mtx[0][3] = 0;
    mtx[1][0] = 0; mtx[1][1] = 1; mtx[1][2] = 0; mtx[1][3] = 0;
    mtx[2][0] = 0; mtx[2][1] = 0; mtx[2][2] = 1; mtx[2][3] = 0;
    mtx[3][0] = 0; mtx[3][1] = 0; mtx[3][2] = 0; mtx[3][3] = 1;
}

void translate(float mtx[4][4], float tx, float ty, float tz)
{
    float t_mtx[4][4];
    float tmp[4][4];

    identity_mtx(t_mtx); 
    identity_mtx(tmp); 
    t_mtx[0][3] = tx;
    t_mtx[1][3] = ty;
    t_mtx[2][3] = tz;
    mtx_multi(mtx, t_mtx, tmp);
    mtx_copy(tmp, mtx);
}