/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: GPL-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-9-14      zbtrs        The first version
 */


#include <stdio.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define rtt_screen_width 480
#define rtt_screen_height 800


int main (int argc, char *argv[]) 
{
    int ret = -1;
    int videoStream;

    

    SDL_Rect rect;
    SDL_Window *win = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *texture = NULL;

    if(( argc != 2 ))
    {
        printf("error input arguments!\n");
        return(1);
    }

    // 默认窗口大小
    int w_width  = rtt_screen_width;
    int w_height = rtt_screen_height;

    // use dummy video driver
    SDL_setenv("SDL_VIDEODRIVER","rtt",1);
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    // 创建窗口
    win = SDL_CreateWindow("Media Player",
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            w_width, w_height,
                            SDL_WINDOW_SHOWN );
    if (!win) 
    {
        printf("Failed to create window by SDL\n");
        goto __exit;
    }

    // 创建渲染器
    renderer = SDL_CreateRenderer(win, -1, 0);
    if (!renderer) 
    {
        printf("Failed to create Renderer by SDL\n");
        goto __exit;
    }
#if 1
    texture = IMG_LoadTexture(renderer, "/root/test.bmp");
    if (!texture) {
        SDL_Log("Couldn't load \n");
        return -1;
    }

    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);

    printf("w = %d, h = %d\n", w, h);
    rect.x = 0;
    rect.y = 0;
    rect.w = w;
    rect.h = h;
    /* Display the image */
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_RenderPresent(renderer);
#endif 
while (1) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                goto __exit;
            }
        }
    }
#if 0
    // 创建纹理
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_IYUV,
                                SDL_TEXTUREACCESS_STREAMING,
                                w_width,
                                w_height);
    if (!texture) {
        printf("SDL_CreateTexture Error: %s\n",SDL_GetError());
        goto __exit;
    }

    const int centerX = 100; // 窗口中心 X 坐标
    const int centerY = 75; // 窗口中心 Y 坐标
    const int crossSize = 20; // 十字线长度（半长）
    const SDL_Color crossColor = {255, 0, 0, 255}; // 红色

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
// 绘制十字线
        SDL_SetRenderDrawColor(renderer, crossColor.r, crossColor.g, crossColor.b, crossColor.a);
        
        // 水平线（左到右）
        SDL_RenderDrawLine(
            renderer,
            centerX - crossSize, centerY, // 起点
            centerX + crossSize, centerY  // 终点
        );
        
        // 垂直线（上到下）
        SDL_RenderDrawLine(
            renderer,
            centerX, centerY - crossSize, // 起点
            centerX, centerY + crossSize  // 终点
        );
 
        // 更新屏幕
        SDL_RenderPresent(renderer);
#endif

    __exit:

    if (win) 
    {
        SDL_DestroyWindow(win);
    }

    if (renderer) 
    {
        SDL_DestroyRenderer(renderer);
    }

    if (texture) 
    {
        SDL_DestroyTexture(texture);
    }

    SDL_Quit();

    return ret;
}