

#ifndef ___LanguageRule___H___
#define ___LanguageRule___H___

#define ORG			     {		// ��ʼ
#define END 		     }		// ����


// variable : ����
// start_val����ʼֵ
// max_val���������ֵ
// add_num���ۼ���
#define FOREACH(variable,start_val,max_val,add_num)	for(variable = start_val;variable < max_val;variable+=add_num)

// �����������ֵʱ���趨ΪĿ��ֵ
#define VARIABLE_TO_MAX_TO_0(variable,MAX,Target_val) variable = variable > MAX ? variable : Target_val

#endif






