#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "multiThreadSorter_thread.h"

Imdbinfo** merge(Imdbinfo** imdb, int cap, char *heading)
{
	if(cap==1)
	{
		return imdb;
	}

    int x;
    int y;
    
    int ptr = 0;
    int ptr2 = 0;
    
    int movcap = 0;

    Imdbinfo **data = (Imdbinfo**)malloc(sizeof(Imdbinfo*)*(cap/2));

    if(cap%2 == 0)
    {
    	movcap = cap/2;
    }
    else
    {
    	movcap = cap/2 + 1;
    }

    Imdbinfo **data2 = (Imdbinfo**)malloc(sizeof(Imdbinfo*)*movcap);

    for(x=0; x<(cap/2); x++)
    {
    	data[x] = imdb[x];
    }
    
    data = merge(data, cap/2, heading);

	for(y=0; y<cap; x++, y++)
	{
		data2[y] = imdb[x];
    }
    
    data2 = merge(data2, movcap, heading);

    if(strcmp(heading, "color") == 0)
    {
    	while(ptr < (cap/2) && ptr2 < movcap)
    	{
    		if( (strcmp(data[ptr]->color, data2[ptr2]->color) == 0) || strlen(data[ptr]->color) == 0)
    		{
    			imdb[ptr+ptr2] = data[ptr];
    			ptr++;
    			continue;
        	}

        	if(strlen(data2[ptr2]->color) == 0)
        	{
        		imdb[ptr+ptr2] = data2[ptr2];
        		ptr2++;
        		continue;
        	}

        	x = 0;
        	y = 0;

        	while(data[ptr]->color[x] && data2[ptr2]->color[y])
        	{
        		if(tolower(data[ptr]->color[x]) == tolower(data2[ptr2]->color[y]))
        		{
        			if(data[ptr]->color[x] == data2[ptr2]->color[y])
        			{
        				x++;
        				y++;
        				continue;
        			}
        			
        			else if(data[ptr]->color[x] < data2[ptr2]->color[y])
        			{
        				imdb[ptr+ptr2] = data[ptr];
        				ptr++;
        			}
        			
        			else
        			{
        				imdb[ptr+ptr2] = data2[ptr2];
        				ptr2++;
            		}

            		break;
            	}

            	if(tolower(data[ptr]->color[x]) < tolower(data2[ptr2]->color[y]))
            	{
            		imdb[ptr+ptr2] = data[ptr];
            		ptr++;
            		break;
          		}
          		
          		else
          		{
            		imdb[ptr+ptr2] = data2[ptr2];
            		ptr2++;
            		break;
          		}
        	}

        	if(ptr < cap/2 && x >= strlen(data[ptr]->color))
        	{
				imdb[ptr+ptr2] = data[ptr];
				ptr++;
			} 

			else if(ptr2 < movcap && y >= strlen(data2[ptr2]->color))
			{
				imdb[ptr+ptr2] = data2[ptr2];
				ptr2++;
			}
		}

		while(ptr < cap/2)
		{
			imdb[ptr+ptr2] = data[ptr];
			ptr++;
		}

		while(ptr2 < movcap)
		{
			imdb[ptr+ptr2] = data2[ptr2];
			ptr2++;
		}
	}

	else if(strcmp(heading, "director_name") == 0)
	{
		while(ptr < (cap/2) && ptr2 < movcap)
		{
			if((strcmp(data[ptr]->director_name, data2[ptr2]->director_name) == 0) || strlen(data[ptr]->director_name) == 0)
			{
				imdb[ptr+ptr2] = data[ptr];
				ptr++;
				continue;
			}

			if(strlen(data2[ptr2]->director_name) == 0)
			{
				imdb[ptr+ptr2] = data2[ptr2];
				ptr2++;
              	continue;
            }

            x = 0;
            y = 0;

            while(data[ptr]->director_name[x] && data2[ptr2]->director_name[y])
            {
            	if(tolower(data[ptr]->director_name[x]) == tolower(data2[ptr2]->director_name[y]))
            	{
            		if(data[ptr]->director_name[x] == data2[ptr2]->director_name[y])
            		{
            			x++;
            			y++;
            			continue;
            		}
            		else if(data[ptr]->director_name[x] < data2[ptr2]->director_name[y])
            		{
            			imdb[ptr+ptr2] = data[ptr];
            			ptr++;
            		}
            		else
            		{
            			imdb[ptr+ptr2] = data2[ptr2];
            			ptr2++;
            		}
            		break;
            	}

            	if(tolower(data[ptr]->director_name[x]) < tolower(data2[ptr2]->director_name[y]))
            	{
            		imdb[ptr+ptr2] = data[ptr];
            		ptr++;
            		break;
            	}
            	else
            	{
            		imdb[ptr+ptr2] = data2[ptr2];
            		ptr2++;
            		break;
            	}
            }

			if(ptr < cap/2 && x >= strlen(data[ptr]->director_name))
			{
			  imdb[ptr+ptr2] = data[ptr];
			  ptr++;
			}
			else if(ptr2 < movcap && y >= strlen(data2[ptr2]->director_name))
			{
				imdb[ptr+ptr2] = data2[ptr2];
				ptr2++;
			}
		}

		while(ptr < cap/2)
		{
			imdb[ptr+ptr2] = data[ptr];
			ptr++;
		}

		while(ptr2 < movcap)
		{
			imdb[ptr+ptr2] = data2[ptr2];
			ptr2++;
		}
	}

	else if(strcmp(heading, "actor_2_name") == 0)
	{
		while(ptr < (cap/2) && ptr2 < movcap)
		{
			if((strcmp(data[ptr]->actor_2_name, data2[ptr2]->actor_2_name) == 0) || strlen(data[ptr]->actor_2_name) == 0)
			{
				imdb[ptr+ptr2] = data[ptr];
				ptr++;
				continue;
			}

			if(strlen(data2[ptr2]->actor_2_name) == 0)
			{
				imdb[ptr+ptr2] = data2[ptr2];
				ptr2++;
              	continue;
            }

            x = 0;
            y = 0;

            while(data[ptr]->actor_2_name[x] && data2[ptr2]->actor_2_name[y])
            {
            	if(tolower(data[ptr]->actor_2_name[x]) == tolower(data2[ptr2]->actor_2_name[y]))
            	{
            		if(data[ptr]->actor_2_name[x] == data2[ptr2]->actor_2_name[y])
            		{
            			x++;
            			y++;
            			continue;
            		}
            		else if(data[ptr]->actor_2_name[x] < data2[ptr2]->actor_2_name[y])
            		{
            			imdb[ptr+ptr2] = data[ptr];
            			ptr++;
            		}
            		else
            		{
            			imdb[ptr+ptr2] = data2[ptr2];
            			ptr2++;
            		}
            		break;
            	}

            	if(tolower(data[ptr]->actor_2_name[x]) < tolower(data2[ptr2]->actor_2_name[y]))
            	{
            		imdb[ptr+ptr2] = data[ptr];
            		ptr++;
            		break;
            	}
            	else
            	{
            		imdb[ptr+ptr2] = data2[ptr2];
            		ptr2++;
            		break;
            	}
            }

			if(ptr < cap/2 && x >= strlen(data[ptr]->actor_2_name))
			{
			  imdb[ptr+ptr2] = data[ptr];
			  ptr++;
			}
			else if(ptr2 < movcap && y >= strlen(data2[ptr2]->actor_2_name))
			{
				imdb[ptr+ptr2] = data2[ptr2];
				ptr2++;
			}
		}

		while(ptr < cap/2)
		{
			imdb[ptr+ptr2] = data[ptr];
			ptr++;
		}

		while(ptr2 < movcap)
		{
			imdb[ptr+ptr2] = data2[ptr2];
			ptr2++;
		}
	}

	else if(strcmp(heading, "genres") == 0)
	{
		while(ptr < (cap/2) && ptr2 < movcap)
		{
			if((strcmp(data[ptr]->genres, data2[ptr2]->genres) == 0) || strlen(data[ptr]->genres) == 0)
			{
				imdb[ptr+ptr2] = data[ptr];
				ptr++;
				continue;
			}

			if(strlen(data2[ptr2]->genres) == 0)
			{
				imdb[ptr+ptr2] = data2[ptr2];
				ptr2++;
              	continue;
            }

            x = 0;
            y = 0;

            while(data[ptr]->genres[x] && data2[ptr2]->genres[y])
            {
            	if(tolower(data[ptr]->genres[x]) == tolower(data2[ptr2]->genres[y]))
            	{
            		if(data[ptr]->genres[x] == data2[ptr2]->genres[y])
            		{
            			x++;
            			y++;
            			continue;
            		}
            		else if(data[ptr]->genres[x] < data2[ptr2]->genres[y])
            		{
            			imdb[ptr+ptr2] = data[ptr];
            			ptr++;
            		}
            		else
            		{
            			imdb[ptr+ptr2] = data2[ptr2];
            			ptr2++;
            		}
            		break;
            	}

            	if(tolower(data[ptr]->genres[x]) < tolower(data2[ptr2]->genres[y]))
            	{
            		imdb[ptr+ptr2] = data[ptr];
            		ptr++;
            		break;
            	}
            	else
            	{
            		imdb[ptr+ptr2] = data2[ptr2];
            		ptr2++;
            		break;
            	}
            }

			if(ptr < cap/2 && x >= strlen(data[ptr]->genres))
			{
			  imdb[ptr+ptr2] = data[ptr];
			  ptr++;
			}
			else if(ptr2 < movcap && y >= strlen(data2[ptr2]->genres))
			{
				imdb[ptr+ptr2] = data2[ptr2];
				ptr2++;
			}
		}

		while(ptr < cap/2)
		{
			imdb[ptr+ptr2] = data[ptr];
			ptr++;
		}

		while(ptr2 < movcap)
		{
			imdb[ptr+ptr2] = data2[ptr2];
			ptr2++;
		}
	}

	else if(strcmp(heading, "actor_1_name") == 0)
	{
		while(ptr < (cap/2) && ptr2 < movcap)
		{
			if((strcmp(data[ptr]->actor_1_name, data2[ptr2]->actor_1_name) == 0) || strlen(data[ptr]->actor_1_name) == 0)
			{
				imdb[ptr+ptr2] = data[ptr];
				ptr++;
				continue;
			}

			if(strlen(data2[ptr2]->actor_1_name) == 0)
			{
				imdb[ptr+ptr2] = data2[ptr2];
				ptr2++;
              	continue;
            }

            x = 0;
            y = 0;

            while(data[ptr]->actor_1_name[x] && data2[ptr2]->actor_1_name[y])
            {
            	if(tolower(data[ptr]->actor_1_name[x]) == tolower(data2[ptr2]->actor_1_name[y]))
            	{
            		if(data[ptr]->actor_1_name[x] == data2[ptr2]->actor_1_name[y])
            		{
            			x++;
            			y++;
            			continue;
            		}
            		else if(data[ptr]->actor_1_name[x] < data2[ptr2]->actor_1_name[y])
            		{
            			imdb[ptr+ptr2] = data[ptr];
            			ptr++;
            		}
            		else
            		{
            			imdb[ptr+ptr2] = data2[ptr2];
            			ptr2++;
            		}
            		break;
            	}

            	if(tolower(data[ptr]->actor_1_name[x]) < tolower(data2[ptr2]->actor_1_name[y]))
            	{
            		imdb[ptr+ptr2] = data[ptr];
            		ptr++;
            		break;
            	}
            	else
            	{
            		imdb[ptr+ptr2] = data2[ptr2];
            		ptr2++;
            		break;
            	}
            }

			if(ptr < cap/2 && x >= strlen(data[ptr]->actor_1_name))
			{
			  imdb[ptr+ptr2] = data[ptr];
			  ptr++;
			}
			else if(ptr2 < movcap && y >= strlen(data2[ptr2]->actor_1_name))
			{
				imdb[ptr+ptr2] = data2[ptr2];
				ptr2++;
			}
		}

		while(ptr < cap/2)
		{
			imdb[ptr+ptr2] = data[ptr];
			ptr++;
		}

		while(ptr2 < movcap)
		{
			imdb[ptr+ptr2] = data2[ptr2];
			ptr2++;
		}
	}

	else if(strcmp(heading, "movie_title") == 0)
	{
		while(ptr < (cap/2) && ptr2 < movcap)
		{
			if((strcmp(data[ptr]->movie_title, data2[ptr2]->movie_title) == 0) || strlen(data[ptr]->movie_title) == 0)
			{
				imdb[ptr+ptr2] = data[ptr];
				ptr++;
				continue;
			}

			if(strlen(data2[ptr2]->movie_title) == 0)
			{
				imdb[ptr+ptr2] = data2[ptr2];
				ptr2++;
              	continue;
            }

            x = 0;
            y = 0;

            while(data[ptr]->movie_title[x] && data2[ptr2]->movie_title[y])
            {
            	if(tolower(data[ptr]->movie_title[x]) == tolower(data2[ptr2]->movie_title[y]))
            	{
            		if(data[ptr]->movie_title[x] == data2[ptr2]->movie_title[y])
            		{
            			x++;
            			y++;
            			continue;
            		}
            		else if(data[ptr]->movie_title[x] < data2[ptr2]->movie_title[y])
            		{
            			imdb[ptr+ptr2] = data[ptr];
            			ptr++;
            		}
            		else
            		{
            			imdb[ptr+ptr2] = data2[ptr2];
            			ptr2++;
            		}
            		break;
            	}

            	if(tolower(data[ptr]->movie_title[x]) < tolower(data2[ptr2]->movie_title[y]))
            	{
            		imdb[ptr+ptr2] = data[ptr];
            		ptr++;
            		break;
            	}
            	else
            	{
            		imdb[ptr+ptr2] = data2[ptr2];
            		ptr2++;
            		break;
            	}
            }

			if(ptr < cap/2 && x >= strlen(data[ptr]->movie_title))
			{
			  imdb[ptr+ptr2] = data[ptr];
			  ptr++;
			}
			else if(ptr2 < movcap && y >= strlen(data2[ptr2]->movie_title))
			{
				imdb[ptr+ptr2] = data2[ptr2];
				ptr2++;
			}
		}

		while(ptr < cap/2)
		{
			imdb[ptr+ptr2] = data[ptr];
			ptr++;
		}

		while(ptr2 < movcap)
		{
			imdb[ptr+ptr2] = data2[ptr2];
			ptr2++;
		}
	}

	else if(strcmp(heading, "actor_3_name") == 0)
	{
		while(ptr < (cap/2) && ptr2 < movcap)
		{
			if((strcmp(data[ptr]->actor_3_name, data2[ptr2]->actor_3_name) == 0) || strlen(data[ptr]->actor_3_name) == 0)
			{
				imdb[ptr+ptr2] = data[ptr];
				ptr++;
				continue;
			}

			if(strlen(data2[ptr2]->actor_3_name) == 0)
			{
				imdb[ptr+ptr2] = data2[ptr2];
				ptr2++;
              	continue;
            }

            x = 0;
            y = 0;

            while(data[ptr]->actor_3_name[x] && data2[ptr2]->actor_3_name[y])
            {
            	if(tolower(data[ptr]->actor_3_name[x]) == tolower(data2[ptr2]->actor_3_name[y]))
            	{
            		if(data[ptr]->actor_3_name[x] == data2[ptr2]->actor_3_name[y])
            		{
            			x++;
            			y++;
            			continue;
            		}
            		else if(data[ptr]->actor_3_name[x] < data2[ptr2]->actor_3_name[y])
            		{
            			imdb[ptr+ptr2] = data[ptr];
            			ptr++;
            		}
            		else
            		{
            			imdb[ptr+ptr2] = data2[ptr2];
            			ptr2++;
            		}
            		break;
            	}

            	if(tolower(data[ptr]->actor_3_name[x]) < tolower(data2[ptr2]->actor_3_name[y]))
            	{
            		imdb[ptr+ptr2] = data[ptr];
            		ptr++;
            		break;
            	}
            	else
            	{
            		imdb[ptr+ptr2] = data2[ptr2];
            		ptr2++;
            		break;
            	}
            }

			if(ptr < cap/2 && x >= strlen(data[ptr]->actor_3_name))
			{
			  imdb[ptr+ptr2] = data[ptr];
			  ptr++;
			}
			else if(ptr2 < movcap && y >= strlen(data2[ptr2]->actor_3_name))
			{
				imdb[ptr+ptr2] = data2[ptr2];
				ptr2++;
			}
		}

		while(ptr < cap/2)
		{
			imdb[ptr+ptr2] = data[ptr];
			ptr++;
		}

		while(ptr2 < movcap)
		{
			imdb[ptr+ptr2] = data2[ptr2];
			ptr2++;
		}
	}

	else if(strcmp(heading, "plot_keywords") == 0)
	{
		while(ptr < (cap/2) && ptr2 < movcap)
		{
			if((strcmp(data[ptr]->plot_keywords, data2[ptr2]->plot_keywords) == 0) || strlen(data[ptr]->plot_keywords) == 0)
			{
				imdb[ptr+ptr2] = data[ptr];
				ptr++;
				continue;
			}

			if(strlen(data2[ptr2]->plot_keywords) == 0)
			{
				imdb[ptr+ptr2] = data2[ptr2];
				ptr2++;
              	continue;
            }

            x = 0;
            y = 0;

            while(data[ptr]->plot_keywords[x] && data2[ptr2]->plot_keywords[y])
            {
            	if(tolower(data[ptr]->plot_keywords[x]) == tolower(data2[ptr2]->plot_keywords[y]))
            	{
            		if(data[ptr]->plot_keywords[x] == data2[ptr2]->plot_keywords[y])
            		{
            			x++;
            			y++;
            			continue;
            		}
            		else if(data[ptr]->plot_keywords[x] < data2[ptr2]->plot_keywords[y])
            		{
            			imdb[ptr+ptr2] = data[ptr];
            			ptr++;
            		}
            		else
            		{
            			imdb[ptr+ptr2] = data2[ptr2];
            			ptr2++;
            		}
            		break;
            	}

            	if(tolower(data[ptr]->plot_keywords[x]) < tolower(data2[ptr2]->plot_keywords[y]))
            	{
            		imdb[ptr+ptr2] = data[ptr];
            		ptr++;
            		break;
            	}
            	else
            	{
            		imdb[ptr+ptr2] = data2[ptr2];
            		ptr2++;
            		break;
            	}
            }

			if(ptr < cap/2 && x >= strlen(data[ptr]->plot_keywords))
			{
			  imdb[ptr+ptr2] = data[ptr];
			  ptr++;
			}
			else if(ptr2 < movcap && y >= strlen(data2[ptr2]->plot_keywords))
			{
				imdb[ptr+ptr2] = data2[ptr2];
				ptr2++;
			}
		}

		while(ptr < cap/2)
		{
			imdb[ptr+ptr2] = data[ptr];
			ptr++;
		}

		while(ptr2 < movcap)
		{
			imdb[ptr+ptr2] = data2[ptr2];
			ptr2++;
		}
	}

	else if(strcmp(heading, "movie_imdb_link") == 0)
	{
		while(ptr < (cap/2) && ptr2 < movcap)
		{
			if((strcmp(data[ptr]->movie_imdb_link, data2[ptr2]->movie_imdb_link) == 0) || strlen(data[ptr]->movie_imdb_link) == 0)
			{
				imdb[ptr+ptr2] = data[ptr];
				ptr++;
				continue;
			}

			if(strlen(data2[ptr2]->movie_imdb_link) == 0)
			{
				imdb[ptr+ptr2] = data2[ptr2];
				ptr2++;
              	continue;
            }

            x = 0;
            y = 0;

            while(data[ptr]->movie_imdb_link[x] && data2[ptr2]->movie_imdb_link[y])
            {
            	if(tolower(data[ptr]->movie_imdb_link[x]) == tolower(data2[ptr2]->movie_imdb_link[y]))
            	{
            		if(data[ptr]->movie_imdb_link[x] == data2[ptr2]->movie_imdb_link[y])
            		{
            			x++;
            			y++;
            			continue;
            		}
            		else if(data[ptr]->movie_imdb_link[x] < data2[ptr2]->movie_imdb_link[y])
            		{
            			imdb[ptr+ptr2] = data[ptr];
            			ptr++;
            		}
            		else
            		{
            			imdb[ptr+ptr2] = data2[ptr2];
            			ptr2++;
            		}
            		break;
            	}

            	if(tolower(data[ptr]->movie_imdb_link[x]) < tolower(data2[ptr2]->movie_imdb_link[y]))
            	{
            		imdb[ptr+ptr2] = data[ptr];
            		ptr++;
            		break;
            	}
            	else
            	{
            		imdb[ptr+ptr2] = data2[ptr2];
            		ptr2++;
            		break;
            	}
            }

			if(ptr < cap/2 && x >= strlen(data[ptr]->movie_imdb_link))
			{
			  imdb[ptr+ptr2] = data[ptr];
			  ptr++;
			}
			else if(ptr2 < movcap && y >= strlen(data2[ptr2]->movie_imdb_link))
			{
				imdb[ptr+ptr2] = data2[ptr2];
				ptr2++;
			}
		}

		while(ptr < cap/2)
		{
			imdb[ptr+ptr2] = data[ptr];
			ptr++;
		}

		while(ptr2 < movcap)
		{
			imdb[ptr+ptr2] = data2[ptr2];
			ptr2++;
		}
	}

	else if(strcmp(heading, "language") == 0)
	{
		while(ptr < (cap/2) && ptr2 < movcap)
		{
			if((strcmp(data[ptr]->language, data2[ptr2]->language) == 0) || strlen(data[ptr]->language) == 0)
			{
				imdb[ptr+ptr2] = data[ptr];
				ptr++;
				continue;
			}

			if(strlen(data2[ptr2]->language) == 0)
			{
				imdb[ptr+ptr2] = data2[ptr2];
				ptr2++;
              	continue;
            }

            x = 0;
            y = 0;

            while(data[ptr]->language[x] && data2[ptr2]->language[y])
            {
            	if(tolower(data[ptr]->language[x]) == tolower(data2[ptr2]->language[y]))
            	{
            		if(data[ptr]->language[x] == data2[ptr2]->language[y])
            		{
            			x++;
            			y++;
            			continue;
            		}
            		else if(data[ptr]->language[x] < data2[ptr2]->language[y])
            		{
            			imdb[ptr+ptr2] = data[ptr];
            			ptr++;
            		}
            		else
            		{
            			imdb[ptr+ptr2] = data2[ptr2];
            			ptr2++;
            		}
            		break;
            	}

            	if(tolower(data[ptr]->language[x]) < tolower(data2[ptr2]->language[y]))
            	{
            		imdb[ptr+ptr2] = data[ptr];
            		ptr++;
            		break;
            	}
            	else
            	{
            		imdb[ptr+ptr2] = data2[ptr2];
            		ptr2++;
            		break;
            	}
            }

			if(ptr < cap/2 && x >= strlen(data[ptr]->language))
			{
			  imdb[ptr+ptr2] = data[ptr];
			  ptr++;
			}
			else if(ptr2 < movcap && y >= strlen(data2[ptr2]->language))
			{
				imdb[ptr+ptr2] = data2[ptr2];
				ptr2++;
			}
		}

		while(ptr < cap/2)
		{
			imdb[ptr+ptr2] = data[ptr];
			ptr++;
		}

		while(ptr2 < movcap)
		{
			imdb[ptr+ptr2] = data2[ptr2];
			ptr2++;
		}
	}

	else if(strcmp(heading, "country") == 0)
	{
		while(ptr < (cap/2) && ptr2 < movcap)
		{
			if((strcmp(data[ptr]->country, data2[ptr2]->country) == 0) || strlen(data[ptr]->country) == 0)
			{
				imdb[ptr+ptr2] = data[ptr];
				ptr++;
				continue;
			}

			if(strlen(data2[ptr2]->country) == 0)
			{
				imdb[ptr+ptr2] = data2[ptr2];
				ptr2++;
              	continue;
            }

            x = 0;
            y = 0;

            while(data[ptr]->country[x] && data2[ptr2]->country[y])
            {
            	if(tolower(data[ptr]->country[x]) == tolower(data2[ptr2]->country[y]))
            	{
            		if(data[ptr]->country[x] == data2[ptr2]->country[y])
            		{
            			x++;
            			y++;
            			continue;
            		}
            		else if(data[ptr]->country[x] < data2[ptr2]->country[y])
            		{
            			imdb[ptr+ptr2] = data[ptr];
            			ptr++;
            		}
            		else
            		{
            			imdb[ptr+ptr2] = data2[ptr2];
            			ptr2++;
            		}
            		break;
            	}

            	if(tolower(data[ptr]->country[x]) < tolower(data2[ptr2]->country[y]))
            	{
            		imdb[ptr+ptr2] = data[ptr];
            		ptr++;
            		break;
            	}
            	else
            	{
            		imdb[ptr+ptr2] = data2[ptr2];
            		ptr2++;
            		break;
            	}
            }

			if(ptr < cap/2 && x >= strlen(data[ptr]->country))
			{
			  imdb[ptr+ptr2] = data[ptr];
			  ptr++;
			}
			else if(ptr2 < movcap && y >= strlen(data2[ptr2]->country))
			{
				imdb[ptr+ptr2] = data2[ptr2];
				ptr2++;
			}
		}

		while(ptr < cap/2)
		{
			imdb[ptr+ptr2] = data[ptr];
			ptr++;
		}

		while(ptr2 < movcap)
		{
			imdb[ptr+ptr2] = data2[ptr2];
			ptr2++;
		}
	}

	else if(strcmp(heading, "content_rating") == 0)
	{
		while(ptr < (cap/2) && ptr2 < movcap)
		{
			if((strcmp(data[ptr]->content_rating, data2[ptr2]->content_rating) == 0) || strlen(data[ptr]->content_rating) == 0)
			{
				imdb[ptr+ptr2] = data[ptr];
				ptr++;
				continue;
			}

			if(strlen(data2[ptr2]->content_rating) == 0)
			{
				imdb[ptr+ptr2] = data2[ptr2];
				ptr2++;
              	continue;
            }

            x = 0;
            y = 0;

            while(data[ptr]->content_rating[x] && data2[ptr2]->content_rating[y])
            {
            	if(tolower(data[ptr]->content_rating[x]) == tolower(data2[ptr2]->content_rating[y]))
            	{
            		if(data[ptr]->content_rating[x] == data2[ptr2]->content_rating[y])
            		{
            			x++;
            			y++;
            			continue;
            		}
            		else if(data[ptr]->content_rating[x] < data2[ptr2]->content_rating[y])
            		{
            			imdb[ptr+ptr2] = data[ptr];
            			ptr++;
            		}
            		else
            		{
            			imdb[ptr+ptr2] = data2[ptr2];
            			ptr2++;
            		}
            		break;
            	}

            	if(tolower(data[ptr]->content_rating[x]) < tolower(data2[ptr2]->content_rating[y]))
            	{
            		imdb[ptr+ptr2] = data[ptr];
            		ptr++;
            		break;
            	}
            	else
            	{
            		imdb[ptr+ptr2] = data2[ptr2];
            		ptr2++;
            		break;
            	}
            }

			if(ptr < cap/2 && x >= strlen(data[ptr]->content_rating))
			{
			  imdb[ptr+ptr2] = data[ptr];
			  ptr++;
			}
			else if(ptr2 < movcap && y >= strlen(data2[ptr2]->content_rating))
			{
				imdb[ptr+ptr2] = data2[ptr2];
				ptr2++;
			}
		}

		while(ptr < cap/2)
		{
			imdb[ptr+ptr2] = data[ptr];
			ptr++;
		}

		while(ptr2 < movcap)
		{
			imdb[ptr+ptr2] = data2[ptr2];
			ptr2++;
		}
	}

	else if(strcmp(heading, "num_critic_for_reviews") == 0)
	{
		while(ptr < (cap/2) && ptr2 < movcap)
		{
			if(data[ptr]->num_critic_for_reviews < data2[ptr2]->num_critic_for_reviews)
			{
				imdb[ptr+ptr2] = data[ptr];
				ptr++;
			}
			else if(data[ptr]->num_critic_for_reviews >= data2[ptr2]->num_critic_for_reviews)
			{
				imdb[ptr+ptr2] = data2[ptr2];
				ptr2++;
			}
		}

		while(ptr < (cap/2))
		{
			imdb[ptr+ptr2] = data[ptr];
			ptr++;
		}
		while(ptr2 < movcap)
		{
			imdb[ptr+ptr2] = data2[ptr2];
			ptr2++;
		}
	}

	else if(strcmp(heading, "duration") == 0)
	{
		while(ptr < (cap/2) && ptr2 < movcap)
		{
			if(data[ptr]->duration < data2[ptr2]->duration)
			{
				imdb[ptr+ptr2] = data[ptr];
				ptr++;
			}
			else if(data[ptr]->duration >= data2[ptr2]->duration)
			{
				imdb[ptr+ptr2] = data2[ptr2];
				ptr2++;
			}
		}

		while(ptr < cap/2)
		{
			imdb[ptr+ptr2] = data[ptr];
			ptr++;
		}
		while(ptr2 < movcap)
		{
			imdb[ptr+ptr2] = data2[ptr2];
			ptr2++;
		}
	}

	else if(strcmp(heading, "director_facebook_likes") == 0)
	{
		while(ptr < (cap/2) && ptr2 < movcap)
		{
			if(data[ptr]->director_facebook_likes < data2[ptr2]->director_facebook_likes)
			{
				imdb[ptr+ptr2] = data[ptr];
				ptr++;
			}
			else if(data[ptr]->director_facebook_likes >= data2[ptr2]->director_facebook_likes)
			{
				imdb[ptr+ptr2] = data2[ptr2];
				ptr2++;
			}
		}

		while(ptr < cap/2)
		{
			imdb[ptr+ptr2] = data[ptr];
			ptr++;
		}
		while(ptr2 < movcap)
		{
			imdb[ptr+ptr2] = data2[ptr2];
			ptr2++;
		}
	}

	else if(strcmp(heading, "actor_3_facebook_likes") == 0)
	{
		while(ptr < (cap/2) && ptr2 < movcap)
		{
			if(data[ptr]->actor_3_facebook_likes < data2[ptr2]->actor_3_facebook_likes)
			{
				imdb[ptr+ptr2] = data[ptr];
				ptr++;
			}
			else if(data[ptr]->actor_3_facebook_likes >= data2[ptr2]->actor_3_facebook_likes)
			{
				imdb[ptr+ptr2] = data2[ptr2];
				ptr2++;
			}
		}

		while(ptr < cap/2)
		{
			imdb[ptr+ptr2] = data[ptr];
			ptr++;
		}
		while(ptr2 < movcap)
		{
			imdb[ptr+ptr2] = data2[ptr2];
			ptr2++;
		}
	}

	else if(strcmp(heading, "actor_1_facebook_likes") == 0)
	{
		while(ptr < (cap/2) && ptr2 < movcap)
		{
			if(data[ptr]->actor_1_facebook_likes < data2[ptr2]->actor_1_facebook_likes)
			{
				imdb[ptr+ptr2] = data[ptr];
				ptr++;
			}
			else if(data[ptr]->actor_1_facebook_likes >= data2[ptr2]->actor_1_facebook_likes)
			{
				imdb[ptr+ptr2] = data2[ptr2];
				ptr2++;
			}
		}

		while(ptr < cap/2)
		{
			imdb[ptr+ptr2] = data[ptr];
			ptr++;
		}
		while(ptr2 < movcap)
		{
			imdb[ptr+ptr2] = data2[ptr2];
			ptr2++;
		}
	}

	else if(strcmp(heading, "gross") == 0)
	{
		while(ptr < (cap/2) && ptr2 < movcap)
		{
			if(data[ptr]->gross < data2[ptr2]->gross)
			{
				imdb[ptr+ptr2] = data[ptr];
				ptr++;
			}
			else if(data[ptr]->gross >= data2[ptr2]->gross)
			{
				imdb[ptr+ptr2] = data2[ptr2];
				ptr2++;
			}
		}

		while(ptr < cap/2)
		{
			imdb[ptr+ptr2] = data[ptr];
			ptr++;
		}
		while(ptr2 < movcap)
		{
			imdb[ptr+ptr2] = data2[ptr2];
			ptr2++;
		}
	}

	else if(strcmp(heading, "num_voted_users") == 0)
	{
		while(ptr < (cap/2) && ptr2 < movcap)
		{
			if(data[ptr]->num_voted_users < data2[ptr2]->num_voted_users)
			{
				imdb[ptr+ptr2] = data[ptr];
				ptr++;
			}
			else if(data[ptr]->num_voted_users >= data2[ptr2]->num_voted_users)
			{
				imdb[ptr+ptr2] = data2[ptr2];
				ptr2++;
			}
		}

		while(ptr < cap/2)
		{
			imdb[ptr+ptr2] = data[ptr];
			ptr++;
		}
		while(ptr2 < movcap)
		{
			imdb[ptr+ptr2] = data2[ptr2];
			ptr2++;
		}
	}

	else if(strcmp(heading, "cast_total_facebook_likes") == 0)
	{
		while(ptr < (cap/2) && ptr2 < movcap)
		{
			if(data[ptr]->cast_total_facebook_likes < data2[ptr2]->cast_total_facebook_likes)
			{
				imdb[ptr+ptr2] = data[ptr];
				ptr++;
			}
			else if(data[ptr]->cast_total_facebook_likes >= data2[ptr2]->cast_total_facebook_likes)
			{
				imdb[ptr+ptr2] = data2[ptr2];
				ptr2++;
			}
		}

		while(ptr < cap/2)
		{
			imdb[ptr+ptr2] = data[ptr];
			ptr++;
		}
		while(ptr2 < movcap)
		{
			imdb[ptr+ptr2] = data2[ptr2];
			ptr2++;
		}
	}

	else if(strcmp(heading, "facenumber_in_poster") == 0)
	{
		while(ptr < (cap/2) && ptr2 < movcap)
		{
			if(data[ptr]->facenumber_in_poster < data2[ptr2]->facenumber_in_poster)
			{
				imdb[ptr+ptr2] = data[ptr];
				ptr++;
			}
			else if(data[ptr]->facenumber_in_poster >= data2[ptr2]->facenumber_in_poster)
			{
				imdb[ptr+ptr2] = data2[ptr2];
				ptr2++;
			}
		}

		while(ptr < cap/2)
		{
			imdb[ptr+ptr2] = data[ptr];
			ptr++;
		}
		while(ptr2 < movcap)
		{
			imdb[ptr+ptr2] = data2[ptr2];
			ptr2++;
		}
	}

	else if(strcmp(heading, "num_user_for_reviews") == 0)
	{
		while(ptr < (cap/2) && ptr2 < movcap)
		{
			if(data[ptr]->num_user_for_reviews < data2[ptr2]->num_user_for_reviews)
			{
				imdb[ptr+ptr2] = data[ptr];
				ptr++;
			}
			else if(data[ptr]->num_user_for_reviews >= data2[ptr2]->num_user_for_reviews)
			{
				imdb[ptr+ptr2] = data2[ptr2];
				ptr2++;
			}
		}

		while(ptr < cap/2)
		{
			imdb[ptr+ptr2] = data[ptr];
			ptr++;
		}
		while(ptr2 < movcap)
		{
			imdb[ptr+ptr2] = data2[ptr2];
			ptr2++;
		}
	}

	else if(strcmp(heading, "budget") == 0)
	{
		while(ptr < (cap/2) && ptr2 < movcap)
		{
			if(data[ptr]->budget < data2[ptr2]->budget)
			{
				imdb[ptr+ptr2] = data[ptr];
				ptr++;
			}
			else if(data[ptr]->budget >= data2[ptr2]->budget)
			{
				imdb[ptr+ptr2] = data2[ptr2];
				ptr2++;
			}
		}

		while(ptr < cap/2)
		{
			imdb[ptr+ptr2] = data[ptr];
			ptr++;
		}
		while(ptr2 < movcap)
		{
			imdb[ptr+ptr2] = data2[ptr2];
			ptr2++;
		}
	}

	else if(strcmp(heading, "title_year") == 0)
	{
		while(ptr < (cap/2) && ptr2 < movcap)
		{
			if(data[ptr]->title_year < data2[ptr2]->title_year)
			{
				imdb[ptr+ptr2] = data[ptr];
				ptr++;
			}
			else if(data[ptr]->title_year >= data2[ptr2]->title_year)
			{
				imdb[ptr+ptr2] = data2[ptr2];
				ptr2++;
			}
		}

		while(ptr < cap/2)
		{
			imdb[ptr+ptr2] = data[ptr];
			ptr++;
		}
		while(ptr2 < movcap)
		{
			imdb[ptr+ptr2] = data2[ptr2];
			ptr2++;
		}
	}

	else if(strcmp(heading, "actor_2_facebook_likes") == 0)
	{
		while(ptr < (cap/2) && ptr2 < movcap)
		{
			if(data[ptr]->actor_2_facebook_likes < data2[ptr2]->actor_2_facebook_likes)
			{
				imdb[ptr+ptr2] = data[ptr];
				ptr++;
			}
			else if(data[ptr]->actor_2_facebook_likes >= data2[ptr2]->actor_2_facebook_likes)
			{
				imdb[ptr+ptr2] = data2[ptr2];
				ptr2++;
			}
		}

		while(ptr < cap/2)
		{
			imdb[ptr+ptr2] = data[ptr];
			ptr++;
		}
		while(ptr2 < movcap)
		{
			imdb[ptr+ptr2] = data2[ptr2];
			ptr2++;
		}
	}

	else if(strcmp(heading, "imdb_score") == 0)
	{
		while(ptr < (cap/2) && ptr2 < movcap)
		{
			if(data[ptr]->imdb_score < data2[ptr2]->imdb_score)
			{
				imdb[ptr+ptr2] = data[ptr];
				ptr++;
			}
			else if(data[ptr]->imdb_score >= data2[ptr2]->imdb_score)
			{
				imdb[ptr+ptr2] = data2[ptr2];
				ptr2++;
			}
		}

		while(ptr < cap/2)
		{
			imdb[ptr+ptr2] = data[ptr];
			ptr++;
		}
		while(ptr2 < movcap)
		{
			imdb[ptr+ptr2] = data2[ptr2];
			ptr2++;
		}
	}

	else if(strcmp(heading, "aspect_ratio") == 0)
	{
		while(ptr < (cap/2) && ptr2 < movcap)
		{
			if(data[ptr]->aspect_ratio < data2[ptr2]->aspect_ratio)
			{
				imdb[ptr+ptr2] = data[ptr];
				ptr++;
			}
			else if(data[ptr]->aspect_ratio >= data2[ptr2]->aspect_ratio)
			{
				imdb[ptr+ptr2] = data2[ptr2];
				ptr2++;
			}
		}

		while(ptr < cap/2)
		{
			imdb[ptr+ptr2] = data[ptr];
			ptr++;
		}
		while(ptr2 < movcap)
		{
			imdb[ptr+ptr2] = data2[ptr2];
			ptr2++;
		}
	}

	else if(strcmp(heading, "movie_facebook_likes") == 0)
	{
		while(ptr < (cap/2) && ptr2 < movcap)
		{
			if(data[ptr]->movie_facebook_likes < data2[ptr2]->movie_facebook_likes)
			{
				imdb[ptr+ptr2] = data[ptr];
				ptr++;
			}
			else if(data[ptr]->movie_facebook_likes >= data2[ptr2]->movie_facebook_likes)
			{
				imdb[ptr+ptr2] = data2[ptr2];
				ptr2++;
			}
		}

		while(ptr < cap/2)
		{
			imdb[ptr+ptr2] = data[ptr];
			ptr++;
		}
		while(ptr2 < movcap)
		{
			imdb[ptr+ptr2] = data2[ptr2];
			ptr2++;
		}
	}

	return imdb;

}

