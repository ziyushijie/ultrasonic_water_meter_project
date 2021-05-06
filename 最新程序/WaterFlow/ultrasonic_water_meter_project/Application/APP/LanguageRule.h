

#ifndef ___LanguageRule___H___
#define ___LanguageRule___H___

#define ORG			     {		// 开始
#define END 		     }		// 结束


// variable : 变量
// start_val：起始值
// max_val：结束最大值
// add_num：累加数
#define FOREACH(variable,start_val,max_val,add_num)	for(variable = start_val;variable < max_val;variable+=add_num)

// 变量到达最大值时，设定为目标值
#define VARIABLE_TO_MAX_TO_0(variable,MAX,Target_val) variable = variable > MAX ? variable : Target_val

#endif






