#ifndef _PP_MATH_EXT_H
	#define _PP_MATH_EXT_H
	
	
//template <typename Type>
//Type trim_pp(Type data, Type upperLimit, Type lowerLimit);

template <typename Type>
Type trim_pp(Type data, Type upperLimit, Type lowerLimit){
		static_assert	(std::is_arithmetic<Type>::value, "<Type> must be integral or a floating point type");
	
	  if(data>=upperLimit)data=upperLimit;
    else if(data<=lowerLimit)data=lowerLimit;

    return data;
	
};

template <typename Type>
Type trimAcc_pp(Type data, Type upperLimit, Type lowerLimit, Type precision){
		static_assert	(std::is_arithmetic<Type>::value, "<Type> must be integral or a floating point type");
	
    data=trim_pp(data, upperLimit, lowerLimit);
	
		int mul=data/precision;
	
		auto rest=data-(mul*precision);
		data=mul*precision;
		
		if(abs(rest)>precision/2){
			if(rest>0)data+=precision;
			else data-=precision;
		}
	
		return data;
}
	
#endif
