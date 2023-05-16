#include <stdint.h>

void user_delayms(int32_t t[2]){
   for(int num = 0; num < t[0]; num++){
      delay_ms(250);
   }
   delay_ms((int8_t)t[1]);
   return;
}

int gps_get(Earth_Coordinates *now, char *buffer, char *gps, int gps_count){
   gets(buffer, gps);
   now->latitude = gps_lat(buffer);
   now->longitude = gps_lon(buffer);
   gps_count++;
   return gps_count;
}


void back_check(Earth_Coordinates *now, float start[2], int f, int j){
   if((fabs(start[0] - now->latitude) < 5 && fabs(start[1] - now->longitude) < 5 && j == 3) || f == 1) {
      if(f == 0){
         fprintf(xbee,"Back Start\r\n");
         back();
         for(int x = 0; x < 4; x++){
            delay_ms(250);
         }
         f=1;
      }else{
         fprintf(xbee,"Rotate Start\r\n");
         right_rotate();
         f=0;
         for(x = 0; x < 4; x++){
            delay_ms(250);
         }
         forward();
      }
   }
   return;
}

void turn_check(Gps_Angles *angles, Motor_Time *time){
   // turn the CanSat with appropriate angle
   if(crs_prod < 0 && angle > 0.05 && j == 0){
      s_time = (int32)(time->left * angle);  //default : 2300s/180degree
      s = s_time / 250;
      s_time = s_time % 250;
      left_turn(); // turn left
      k++;
      for(int x = 0; x < s; x++){
         delay_ms(250);
      }
      delay_ms((int8)s_time);
      forward();
         
      angles->left = angle * 180;

   }
   if(crs_prod > 0 && angle > 0.05 && j == 0){
      s_time = (int32)(time->right * angle);   //default : 2400
      s = s_time / 250;
      s_time = s_time % 250;
      right_turn(); // turn right
      k--;
      for(x = 0; x < s; x++){
         delay_ms(250);
      }
      delay_ms((int8)s_time);
      forward();
         
      angles->right = angle * 180;

   }
   return;
}

typedef struct {
   float now_x;
   float now_y;
   float goal_x;
   float goal_y;
   float dist_x;
   float dist_y;
} calculate_dist;

float calc_dist(Earth_Coordinates *now, Earth_Coordinates *start, Goals *goal){
   // init values
   calculate_dist tmp;
   tmp.now_x = now->latitude - start->latitude;
   tmp.now_y = now->longitude - start->longitude;     
   tmp.goal_x = goal->latitude - start->latitude;
   tmp.goal_y = goal->longitude - start->longitude;
   tmp.dist_x = tmp.goal_y - tmp.now_y;
   tmp.dist_y = tmp.goal_y - tmp.now_y; 

   float dist = sqrt((tmp.dist_x * tmp.dist_x) + (tmp.dist_y * tmp.dist_y));

   return dist;
}

float calc_angle(Earth_Coordinates *now, Earth_Coordinates *start, Goals *goal){
   // init values
   calculate_dist tmp;
   tmp.now_x = now->latitude - start->latitude;
   tmp.now_y = now->longitude - start->longitude;     
   tmp.goal_x = goal->latitude - start->latitude;
   tmp.goal_y = goal->longitude - start->longitude;
   tmp.dist_x = tmp.goal_y - tmp.now_y;
   tmp.dist_y = tmp.goal_y - tmp.now_y; 
   float pi = acos(-1.0);
   float now_tmp, goal_tmp, in_product;

   now_tmp = tmp.now_x * tmp.now_x + tmp.now_y * tmp.now_y;
   goal_tmp = tmp.goal_x * tmp.goal_x + tmp.goal_y * tmp.goal_y;
   in_product = tmp.now_x * tmp.goal_x + tmp.now_y * tmp.goal_y;

   float angle = acos(in_product / (sqrt(now_tmp) * sqrt(goal_tmp))) / pi;

   return angle;
}
