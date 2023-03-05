void user_delayms(int32 t){
   int32 t1,t2,num;
   /*t1 = t / 250;
   t2 = t % 250;
   fprintf(xbee,"t1 = %ld t2 = %ld \r\n",t1,t2);*/
   for(num = 0; num < t1; num++){
      delay_ms(250);
   }
   delay_ms((int8)t2);
   return;
}

void gps_get(void){
   gets(buffer, gps);
   n_posi = gps_lat(buffer);
   e_posi = gps_lon(buffer);
   //fprintf(xbee,"lat = %f\r\n",n_posi);
   //fprintf(xbee,"lon = %f\r\n",e_posi);
   gps_rcv++;
   return;
}


void back_check(void){
      if((fabs(zero[0] - e_posi)<5 && fabs(zero[1]-n_posi)<5 && j==3)||f==1) {
         
         if(f==0){
            fprintf(xbee,"Back Start\r\n");
            back();
            for(x = 0; x < 4; x++)
            {
               delay_ms(250);
            }
            f=1;
         }else{
            fprintf(xbee,"Rotate Start\r\n");
            right_rotate();
            f=0;
            for(x = 0; x < 4; x++)
            {
               delay_ms(250);
            }
            forward();
          }
      }
   return;
}

void turn_check(void){
// turn the CanSat with appropriate angle
      if(crs_prod < 0 && angle > 0.05 && j == 0)
      {
         s_time = (int32)(left_time * angle);  //default : 2300s/180degree
         s = s_time / 250;
         s_time = s_time % 250;
         left_turn(); // turn left
         k++;
         for(x = 0; x < s; x++)
         {
            delay_ms(250);
         }
         delay_ms((int8)s_time);
         forward();
         
         left_angle = angle * 180;

      }
      if(crs_prod > 0 && angle > 0.05 && j == 0)
      {
         s_time = (int32)(right_time * angle);   //default : 2400
         s = s_time / 250;
         s_time = s_time % 250;
         right_turn(); // turn right
         k--;
         for(x = 0; x < s; x++)
         {
            delay_ms(250);
         }
         delay_ms((int8)s_time);
         forward();
         
         right_angle = angle *180;

      }
      return;
}

void calculate(void){
//coordinate origin adjust
        bef_abs_dest_a = abs_dest_a;

        vec_a[0]=e_posi-zero[0];
        vec_a[1]=n_posi-zero[1];
        dest[0]=des_e_posi-zero[0];
        dest[1]=des_n_posi-zero[1];
        dest_a[0]=dest[0]-vec_a[0];
        dest_a[1]=dest[1]-vec_a[1];
        right_angle = 0;
        left_angle = 0;
         if(j == 0)
         {
            zero[0]=e_posi;
            zero[1]=n_posi;
         }
//absolute value of "dest_a"
       abs_dest_a=(dest_a[0])*(dest_a[0])+(dest_a[1])*(dest_a[1]);
       abs_dest_a=sqrt(abs_dest_a);
       
//absolute value of "vec_a"
       abs_vec_a=(vec_a[0])*(vec_a[0])+(vec_a[1])*(vec_a[1]);
       abs_vec_a=sqrt(abs_vec_a);
       
       
       
//inner product of "dest_a" and "vec_a"
       in_prod=(dest_a[0]*vec_a[0])+(dest_a[1]*vec_a[1]);
       in_prod=in_prod/(abs_dest_a * abs_vec_a);
       
//cross product of "dest_a" and "vec_a"
      crs_prod=(dest_a[0]*vec_a[1])-(dest_a[1]*vec_a[0]);

//turn angle calculation
      angle = acos((float32)in_prod);
      angle = angle / pai;
      
   return;
}
