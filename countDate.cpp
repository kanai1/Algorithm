const int month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

struct date
{
   int year, month, day;
};

int leapyear(int year) //윤년이면 1 평년이면 0
{
   if(!(year%400)) return 1;
   if(!(year%100)) return 0;
   if(!(year%4)) return 1;
   return 0;
}

int countDate(struct date day)
{
   int sum = 0;

   //년도에 따른 날짜
   for(int i = 0; i < day.year; i++)
   {
      sum+=(365+leapyear(i));
   }

   //달에 따른 날짜
   for(int i = 1; i < day.month; i++) sum+=month[i];
   if(day.month > 2) sum+=leapyear(day.year);

   //일에 따른 날짜
   sum+=(day.day);

   return sum; //0년 1월 1일 = 1
}
