#pragma once


namespace zm
{

	template<typename _T>
		struct SingleTon :public _T
	{
		static _T& Instance(){
			static _T t;
			return t;
		}

		static _T& Ins(){
			static _T t;
			return t;
		}

		private:
		SingleTon(){}
	};



	template<typename _T>
		struct Singleton :public _T
	{
		static _T& Instance(){
			static _T t;
			return t;
		}
		static _T& Ins(){
			static _T t;
			return t;
		}

		private:
		Singleton(){}
	};

}

