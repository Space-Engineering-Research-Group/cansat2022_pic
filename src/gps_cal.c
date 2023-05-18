/// @brief calcurate to turn the CanSat with appropriate angle
typedef struct {
   double left;
   double right;
} Motor_Time;

typedef struct {
   long int left;
   long int right;
} Gps_Angles;

struct Coordinates {
   float latitude;
   float longitude;
   float height;
};

struct Points {
   struct Coordinates now;
   struct Coordinates start;
   struct Coordinates goal;
};

int get_counts(struct Points *points, char *buffer, char gps, int gps_count){
   gets(buffer, gps);
   points->now.latitude = get_latitude(buffer);
   points->now.longitude = get_longitude(buffer);
   gps_count++;
   return gps_count;
}


void back_check(struct Points *points, struct Pins *pins, bool check, int count){
   if(
      (fabs(points->start.latitude - points->now.latitude) < 5
    && fabs(points->start.longitude - points->now.longitude) < 5 
    && count == 3) 
    || check == true
   ){
      if(check == false){
         fprintf(xbee,"Back Start\r\n");
         back(pins);
         for(int x = 0; x < 4; x++){
            delay_ms(250);
         }
         check = true;
      }else{
         fprintf(xbee,"Rotate Start\r\n");
         right_rotate(pins);
         check = false;
         for(int x = 0; x < 4; x++){
            delay_ms(250);
         }
         forword(pins);
      }
   }
   return;
}

void turn_check(
   Motor_Time *time,
   Gps_Angles *angles,
   struct Pins *pins,
   float angle,
   float cross_product,
   int direction,
   int count
){
   int angle_time, turn_time;
   const int delay = 250;

   // turn the CanSat with appropriate angle
   if(cross_product < 0 && angle > 0.05 && count == 0){
      angle_time = (int)(time->left * angle);  //default : 2300s/180degree
      turn_time = angle_time / delay;
      angle_time = angle_time % delay;
      left_turn(pins); // turn left
      direction++;
      for(int x = 0; x < turn_time; x++){
         delay_ms(delay);
      }
      delay_ms((int)angle_time);
      forword(pins);
         
      angles->left = angle * 180;

   }else if(cross_product > 0 && angle > 0.05 && count == 0){
      angle_time = (int)(time->right * angle);   //default : 2400
      turn_time = angle_time / delay;
      angle_time = angle_time % delay;
      right_turn(pins); // turn right
      direction--;
      for(int x = 0; x < turn_time; x++){
         delay_ms(delay);
      }
      delay_ms((int)angle_time);
      forword(pins);
         
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

float calc_dist(struct Points *points){
   // init values
   calculate_dist tmp;
   tmp.now_x = points->now.latitude - points->start.latitude;
   tmp.now_y = points->now.longitude - points->start.longitude;     
   tmp.goal_x = points->goal.latitude - points->start.latitude;
   tmp.goal_y = points->goal.longitude - points->start.longitude;
   tmp.dist_x = tmp.goal_y - tmp.now_y;
   tmp.dist_y = tmp.goal_y - tmp.now_y; 

   float dist = sqrt((tmp.dist_x * tmp.dist_x) + (tmp.dist_y * tmp.dist_y));

   return dist;
}

typedef struct {
   float inner;
   float cross;
} product;

float calc_angle(struct Points *points, product *prod){
   // init values
   calculate_dist tmp;
   tmp.now_x = points->now.latitude - points->start.latitude;
   tmp.now_y = points->now.longitude - points->start.longitude;     
   tmp.goal_x = points->goal.latitude - points->start.latitude;
   tmp.goal_y = points->goal.longitude - points->start.longitude;
   tmp.dist_x = tmp.goal_y - tmp.now_y;
   tmp.dist_y = tmp.goal_y - tmp.now_y; 
   float pi = acos(-1.0);
   float now_tmp, goal_tmp;

   now_tmp = tmp.now_x * tmp.now_x + tmp.now_y * tmp.now_y;
   goal_tmp = tmp.goal_x * tmp.goal_x + tmp.goal_y * tmp.goal_y;
   prod->inner = tmp.now_x * tmp.goal_x + tmp.now_y * tmp.goal_y;
   prod->cross = tmp.now_x * tmp.goal_x + tmp.now_y * tmp.goal_y;

   float angle = acos(prod->inner / (sqrt(now_tmp) * sqrt(goal_tmp))) / pi;

   return angle;
}
