#include <iostream>
#include <string>   
#include <vector>   


   

#include "Zstd__SimpleCompression.h"
#include "Zstd__Stream__UnknownFinalSize.h"
#include "Zstd__Stream__Lambda__UnknownFinalSize.h"
#include "Zstd__Stream__KnownFinalSize.h"
#include "Zstd__Stream__Lambda__KnownFinalSize.h"
#include "Zstd__DictonaryCompression.h"






int main()
{



	//1-Zstd__SimpleCompression
	//2-Zstd__Stream__KnownFinalSize
	//3-Zstd__Stream__UnknownFinalSize
	//4-Zstd__Stream__Lambda__UnknownFinalSize
	//5-Zstd__Stream__Lambda__KnownFinalSize
	//6-Zstd__DictonaryCompression




	//************************************************************************************1-Zstd__SimpleCompression:Начало************************************************************************************


	Zstd__SimpleCompression Zstd__SimpleCompression_;


	//Методы:
	//- run_Compress
	//- run_Uncompress
	//- run_Uncompress_AutoDetectedSize
	//- set__param_Compress
	//- ResetContext_Compress
	//- set__param_Uncompress
	//- ResetContext_Uncompress



	std::string balvanka_1_1 = "Hello1_Hello2_Hello3_Hello4_Hello5_Hello6_Hello7_Hello8_Hello9_Hello10!!!";
	std::string balvanka_1_2 = "Buy1_Buy2_Buy3_Buy4_Buy5_Buy6_Buy7_Buy8_Buy9_Buy10xxx";



	Zstd__SimpleCompression::result_flag result_1;



	//------------------------------------------------------------------------------run_Compress:Начало---------------------------------------------------------------------------

	//Функция сжимает буффер с указанными данными.


	//--------------------------------------------------------------------------------
	const int level_compressed_1 = 21;                                              //Уровень сжатия: от 0 до 22. 0 - без сжатия ... 22 - масимальное сжатие.

	const char* char_p__to_data_should_be_compressed_4 = &balvanka_1_1[0];          //Указатель на данные, которые нужно Сжать. Это не обязательно должна быть Си-строка, это указатель на любые данные.

	const size_t size__data_to_be_compressed_4 = balvanka_1_1.size();               //Размер данных по указателю, который должен быть Сжат. 

	std::string string_compressed_result_1;                                         //Сюда в случае успеха - функция добавит в конец сжатые данные в соотвествии с установленными парамтерами. В случае ошибки, память будет возвращена к тому значению, которое было до вызова функии.
	//--------------------------------------------------------------------------------




	//------------------------------------------------------------------------------------------
	result_1 = Zstd__SimpleCompression_.run_Compress(level_compressed_1, char_p__to_data_should_be_compressed_4, size__data_to_be_compressed_4, string_compressed_result_1);

	if (result_1 != Zstd__SimpleCompression::result_flag::OK)
	{
		std::cout << "Error_1:" << Zstd__SimpleCompression_.get__ErrorName() << std::endl;

		return -1;
	}
	else
	{
		std::cout << "string_compressed_result_1:" << string_compressed_result_1.size() << std::endl;
		std::cout << "string_compressed_result_1:" << string_compressed_result_1 << std::endl;
	}
	//------------------------------------------------------------------------------------------




	//------------------------------------------------------------------------------------------
	//string_compressed_result_1.resize(0);        //Так как функция добавляет Сжатые данные в конец переданного обьекта строки, то если там уже есть какие то данные, а записать нужно к примеру с начала, то перед вызвом функции нужно обнулить, если нужно чтобы в строке шли подряд два Фрейма сжатых данных, то менять размер соовтетвенно не нужно.

	result_1 = Zstd__SimpleCompression_.run_Compress(15, &balvanka_1_2[0], balvanka_1_2.size(), string_compressed_result_1);

	//------------------------------------------------------------------------------------------
	if (result_1 != Zstd__SimpleCompression::result_flag::OK)
	{
		std::cout << "Error_1:" << Zstd__SimpleCompression_.get__ErrorName() << std::endl;

		return -1;
	}
	else
	{
		std::cout << "string_compressed_result_1:" << string_compressed_result_1.size() << std::endl;
		std::cout << "string_compressed_result_1:" << string_compressed_result_1 << std::endl;
	}
	//------------------------------------------------------------------------------------------


	//------------------------------------------------------------------------------run_Compress:Конец---------------------------------------------------------------------------


	



	//-----------------------------------------------------------------------------run_Uncompress:Начало---------------------------------------------------------------------------

	//Функция расжимает ранее сжатые данные.


	//--------------------------------------------------------
	const char* char_p__to_compressed_data_1_1 = &string_compressed_result_1[0];               //Указатель на данные, которые ранее были сжаты и которые нужно разжать.

	const size_t size__compressed_data_1_1 = string_compressed_result_1.size();              //Размер данных по указателю на данные, которые ранее были сжаты и которые нужно разжать.

	const size_t size__Beforecompressed_data_1_1 = balvanka_1_1.size() + balvanka_1_2.size();   //Размер данных, которые нужно расжать, которые были до Сжатия.

	std::string string_Uncompressed_result_1_1;                                               //Сюда в случае успеха - функция добавит в конец сжатые данные в соотвествии с установленными парамтерами. В случае ошибки, память будет возвращена к тому значению, которое было до вызова функии.
	//--------------------------------------------------------




	//------------------------------------------------------------------------------------------
	
	//string_Uncompressed_result_10_1.resize(0);        //Так как функция добавляет Разжатые данные в конец переданного обьекта строки, то если там уже есть какие то данные, а записать нужно к примеру с начала, то перед вызвом функции нужно обнулить, если нужно чтобы в строке шли подряд два Фрейма сжатых данных, то менять размер соовтетвенно не нужно.
	
	result_1 = Zstd__SimpleCompression_.run_Uncompress(string_Uncompressed_result_1_1, char_p__to_compressed_data_1_1, size__compressed_data_1_1, size__Beforecompressed_data_1_1);

	if (result_1 != Zstd__SimpleCompression::result_flag::OK)
	{
		std::cout << "Error_1:" << Zstd__SimpleCompression_.get__ErrorName() << std::endl;

		return -1;
	}
	else
	{
		std::cout << "string_Uncompressed_result_1_1:" << string_Uncompressed_result_1_1.size() << std::endl;
		std::cout << "string_Uncompressed_result_1_1:" << string_Uncompressed_result_1_1 << std::endl;
	}
	//------------------------------------------------------------------------------------------


	//-----------------------------------------------------------------------------run_Uncompress:Конец---------------------------------------------------------------------------







	//------------------------------------------------------------------------run_Uncompress_AutoDetectedSize:Начало---------------------------------------------------------------------------

	//Функция расжимает ранее сжатые данные, НО в отличии от функции "run_Uncompress" не требует для расжатия данных - размер данных, который был ДО Сжатия. Данный размер определяется внутри функции автоматически по заголовкам Фреймов сжатых данных.
	//Сжатых данных в указанном буффер для расжатия может быть доавблено сколько угодно, Едисвенное условие, что бы эти сжатые данные распологались строго друг за другом, без единого байта пропуска.


	//--------------------------------------------------------
	const char* char_p__to_compressed_data_1_2 = &string_compressed_result_1[0];               //Указатель на данные, которые ранее были сжаты и которые нужно разжать.

	const size_t size__compressed_data_1_2 = string_compressed_result_1.size();              //Размер данных по указателю на данные, которые ранее были сжаты и которые нужно разжать.

	std::string string_Uncompressed_result_1_2;                                               //Сюда в случае успеха - функция добавит в конец сжатые данные в соотвествии с установленными парамтерами. В случае ошибки, память будет возвращена к тому значению, которое было до вызова функии.
	//--------------------------------------------------------




	//------------------------------------------------------------------------------------------

	//string_Uncompressed_result_10_1.resize(0);        //Так как функция добавляет Разжатые данные в конец переданного обьекта строки, то если там уже есть какие то данные, а записать нужно к примеру с начала, то перед вызвом функции нужно обнулить, если нужно чтобы в строке шли подряд два Фрейма сжатых данных, то менять размер соовтетвенно не нужно.

	result_1 = Zstd__SimpleCompression_.run_Uncompress_AutoDetectedSize(string_Uncompressed_result_1_2, char_p__to_compressed_data_1_2, size__compressed_data_1_2);

	if (result_1 != Zstd__SimpleCompression::result_flag::OK)
	{
		std::cout << "Error_1:" << Zstd__SimpleCompression_.get__ErrorName() << std::endl;

		return -1;
	}
	else
	{
		std::cout << "string_Uncompressed_result_1_2:" << string_Uncompressed_result_1_2.size() << std::endl;
		std::cout << "string_Uncompressed_result_1_2:" << string_Uncompressed_result_1_2 << std::endl;
	}
	//------------------------------------------------------------------------------------------




	//------------------------------------------------------------------------run_Uncompress_AutoDetectedSize:Конец---------------------------------------------------------------------------








	//--------------------------------------------------------------------------set__param_Сompress:Начало---------------------------------------------------------------------------

	//Данная фукнция вызывает внутри "ZSTD_CCtx_setParameter" устанавливая дополнительно настраиваемые параметры сжатия.

		//---------------------------------------------------
		//Параметры и их описания, которые принимает функция ZSTD_CCtx_setParameter можно найти или в документации на странице: https://facebook.github.io/zstd/zstd_manual.html   - смотреть enum ZSTD_cParameter.
		//Или в исxодном файле zstd.h - смотреть тот же enum ZSTD_cParameter.

		//ZSTD_cParam_getBounds - данная функция принимает один из параметров "ZSTD_cParameter" и возвращает его минимальное и максимальное значение, которое предается в функцию "ZSTD_CCtx_setParameter" третьим "param_value" параметром.
		//ZSTD_bounds ZSTD_bounds_1 = ZSTD_cParam_getBounds(ZSTD_c_nbWorkers);
		//std::cout << "минимальные значение параметра:" << ZSTD_bounds_1.lowerBound << std::endl;
		//std::cout << "максимальное значение параметра:" << ZSTD_bounds_1.upperBound << std::endl;

		//Проверку на ошибку после вызова через  ZSTD_isError.
		//---------------------------------------------------



	//------------------------------------------------------------------------------------

	const ZSTD_cParameter param_1с = ZSTD_c_minMatch;  //Какой то один из параметров.
	const int param_value_1с = ZSTD_cParam_getBounds(param_1с).lowerBound;

	result_1 = Zstd__SimpleCompression_.set__param_Compress(param_1с, param_value_1с);


	//------------------------------------------------------------------------------------------
	if (result_1 != Zstd__SimpleCompression::result_flag::OK)
	{
		std::cout << "error_1:" << Zstd__SimpleCompression_.get__ErrorName() << std::endl;

		return -1;
	}

	//------------------------------------------------------------------------------------


	//--------------------------------------------------------------------------set__param_Сompress:Начало---------------------------------------------------------------------------




	//--------------------------------------------------------------------------set__param_Uncompress:Начало---------------------------------------------------------------------------

	//Данная фукнция вызывает внутри "ZSTD_DCtx_setParameter" устанавливая дополнительно настраиваемые параметры дэкомпрессии.

		//---------------------------------------------------
		//Параметры и их описание, которые принимает функция ZSTD_DCtx_setParameter можно найти или в документации на странице: https://facebook.github.io/zstd/zstd_manual.html   - смотреть enum ZSTD_dParameter.
		//Или в исxодном файле zstd.h - смотреть тот же enum ZSTD_dParameter.


		//ZSTD_dParam_getBounds - данная функция принимает один из параметров "ZSTD_dParameter" и возвращает его минимальное и максимальное значение, которое предается в функцию "ZSTD_DCtx_setParameter" третьим "param_value" параметром.
		//ZSTD_bounds ZSTD_bounds_1 = ZSTD_dParam_getBounds(ZSTD_d_windowLogMax);
		//std::cout << "минимальные значение параметра:" << ZSTD_bounds_1.lowerBound << std::endl;
		//std::cout << "максимальное значение параметра:" << ZSTD_bounds_1.upperBound << std::endl;

		//Проверку на ошибку после вызова через ZSTD_isError.

		//---------------------------------------------------




	//------------------------------------------------------------------------------------
	const ZSTD_dParameter param_1d = ZSTD_d_windowLogMax;  //Какой то один из параметров.
	const int param_value_1d = ZSTD_dParam_getBounds(param_1d).lowerBound;

	result_1 = Zstd__SimpleCompression_.set__param_Uncompress(param_1d, param_value_1d);


	//------------------------------------------------------------------------------------------
	if (result_1 != Zstd__SimpleCompression::result_flag::OK)
	{
		std::cout << "error_1:" << Zstd__SimpleCompression_.get__ErrorName() << std::endl;

		return -1;
	}

	//------------------------------------------------------------------------------------



	//--------------------------------------------------------------------------set__param_Uncompress:Конец---------------------------------------------------------------------------




	//--------------------------------------------------------------------------------ResetContext_Compress:Начало--------------------------------------------------------------------------------------

	//Вообщем данная функция внутри вызывает "ZSTD_CCtx_reset" то есь сбрасывает сосояние контекста дэкомпрессии. Как написано в документации: https://facebook.github.io/zstd/zstd_manual.html

	//Функция принимает тип "ZSTD_ResetDirective" смотреть в файле zstd.h:

	//typedef enum 
	//{
	//	ZSTD_reset_session_only = 1,
	//	ZSTD_reset_parameters = 2,
	//	ZSTD_reset_session_and_parameters = 3
	//} ZSTD_ResetDirective;


	//There are 2 different things that can be reset, independently or jointly : 
	//-ZSTD_reset_session_only:            The session : will stop compressing current frame, and make CCtx ready to start a new one.Useful after an error, or to interrupt any ongoing compression.Any internal data not yet flushed is cancelled.Compression parameters and dictionary remain unchanged.They will be used to compress next frame.Resetting session never fails. 
	//-ZSTD_reset_parameters:              The parameters : changes all parameters back to "default".This removes any reference to any dictionary too.Parameters can only be changed between 2 sessions(i.e.no compression is currently ongoing) otherwise the reset fails, and function returns an error value(which can be tested using ZSTD_isError()) 
	//-ZSTD_reset_session_and_parameters:  Both : similar to resetting the session, followed by resetting parameters.

	//Есть 2 разных параметра, которые можно сбросить, независимо или совместно:
	//-ZSTD_reset_session_only:           Сессия: прекратит сжатие текущего кадра и подготовит CCtx к началу нового. Полезно после ошибки или для прерывания любого текущего сжатия. Любые внутренние данные, которые еще не были сброшены, отменяются. Параметры сжатия и словарь остаются неизменными. Они будут использоваться для сжатия следующего кадра. Сброс сеанса никогда не приводит к сбою.
	//-ZSTD_reset_parameters:             Параметры: изменяют все параметры обратно на «по умолчанию». Это также удаляет любые ссылки на любой словарь. Параметры можно изменять только между 2 сеансами (т. е. в данный момент сжатие не выполняется), в противном случае сброс не выполняется, и функция возвращает значение ошибки (которое можно проверить с помощью ZSTD_isError())
	//-ZSTD_reset_session_and_parameters: Оба: аналогично сбросу сеанса с последующим сбросом параметров.

	//Честно говоря хрен знает на что эти сбросы особо влияют, единсвенно что более менее понятно - это сброc "ZSTD_reset_parameters" - который сбрасывает все ранее дополнительно установленные параметры с помощью функции "set__param" - в состояние по умолчанию - ну так уровень сжатия, уровни скорости сжатия, окно буффера и прочие магические праметры.


	ZSTD_ResetDirective reset_param_1c = ZSTD_reset_parameters;

	result_1 = Zstd__SimpleCompression_.ResetContext_Compress(reset_param_1c);


	//------------------------------------------------------------------------------------------
	if (result_1 != Zstd__SimpleCompression::result_flag::OK)
	{
		std::cout << "error_1:" << Zstd__SimpleCompression_.get__ErrorName() << std::endl;

		return -1;
	}

	//------------------------------------------------------------------------------------


	//--------------------------------------------------------------------------------ResetContext_Compress:Конец--------------------------------------------------------------------------------------






	//--------------------------------------------------------------------------------ResetContext_Uncompress:Начало--------------------------------------------------------------------------------------

	//Вообщем данная функция внутри вызывает "ZSTD_DCtx_reset" то есь сбрасывает сосояние контекста дэкомпрессии. Как написано в документации: https://facebook.github.io/zstd/zstd_manual.html

	//Функция принимает тип "ZSTD_ResetDirective" смотреть в файле zstd.h:

	//typedef enum 
	//{
	//	ZSTD_reset_session_only = 1,
	//	ZSTD_reset_parameters = 2,
	//	ZSTD_reset_session_and_parameters = 3
	//} ZSTD_ResetDirective;


	//There are 2 different things that can be reset, independently or jointly : 
	//-ZSTD_reset_session_only:            The session : will stop compressing current frame, and make CCtx ready to start a new one.Useful after an error, or to interrupt any ongoing compression.Any internal data not yet flushed is cancelled.Compression parameters and dictionary remain unchanged.They will be used to compress next frame.Resetting session never fails. 
	//-ZSTD_reset_parameters:              The parameters : changes all parameters back to "default".This removes any reference to any dictionary too.Parameters can only be changed between 2 sessions(i.e.no compression is currently ongoing) otherwise the reset fails, and function returns an error value(which can be tested using ZSTD_isError()) 
	//-ZSTD_reset_session_and_parameters:  Both : similar to resetting the session, followed by resetting parameters.

	//Есть 2 разных параметра, которые можно сбросить, независимо или совместно:
	//-ZSTD_reset_session_only:           Сессия: прекратит сжатие текущего кадра и подготовит CCtx к началу нового. Полезно после ошибки или для прерывания любого текущего сжатия. Любые внутренние данные, которые еще не были сброшены, отменяются. Параметры сжатия и словарь остаются неизменными. Они будут использоваться для сжатия следующего кадра. Сброс сеанса никогда не приводит к сбою.
	//-ZSTD_reset_parameters:             Параметры: изменяют все параметры обратно на «по умолчанию». Это также удаляет любые ссылки на любой словарь. Параметры можно изменять только между 2 сеансами (т. е. в данный момент сжатие не выполняется), в противном случае сброс не выполняется, и функция возвращает значение ошибки (которое можно проверить с помощью ZSTD_isError())
	//-ZSTD_reset_session_and_parameters: Оба: аналогично сбросу сеанса с последующим сбросом параметров.

	//Честно говоря хрен знает на что эти сбросы особо влияют, единсвенно что более менее понятно - это сброc "ZSTD_reset_parameters" - который сбрасывает все ранее дополнительно установленные параметры с помощью функции "set__param" - в состояние по умолчанию - ну так уровень сжатия, уровни скорости сжатия, окно буффера и прочие магические праметры.


	ZSTD_ResetDirective reset_param_1d = ZSTD_reset_parameters;

	result_1 = Zstd__SimpleCompression_.ResetContext_Uncompress(reset_param_1d);


	//------------------------------------------------------------------------------------------
	if (result_1 != Zstd__SimpleCompression::result_flag::OK)
	{
		std::cout << "error_1:" << Zstd__SimpleCompression_.get__ErrorName() << std::endl;

		return -1;
	}

	//------------------------------------------------------------------------------------


	//--------------------------------------------------------------------------------ResetContext_Uncompress:Конец--------------------------------------------------------------------------------------



	//************************************************************************************1-Zstd__SimpleCompression:Конец************************************************************************************


















	//************************************************************************************2-Zstd__Stream__KnownFinalSize:Начало************************************************************************************
	//Данная функция сжимает "потоковые данные" целевого "файла" по частям: размер всего итогового "файла" нужно знать и указывать заранее.
	//Важно: Сжатие по частям, когда часть меньше размера самого буффера с данными - естесвенно менее эффективно по итогвому результату, если бы сжатие происходило бы всего буффера с входящими данными.
	//БОЛЕЕ ПОДРОБНО: предположим условно что с сети пришла часть файла, то есть просто массив данных известного размера, вызываем "run_StartStream" с флагом Stream_flag::continue_stream, теперь приходить вторая часть, НЕ Последняя из этого файла, вызываем "run_ContinueStream" с флагом Stream_flag::continue_stream, а теперь приходить тридцать вторая часть этого файла последняя, то есть эта часть завершающая часть этого файла, то для это части нужно вызвать Stream_flag::end_stream. 
	//ВОПРОС: однако я нифига не понимаю, в чем смысл использовать именно функцию потокового сжатия "ZSTD_compressStream2" для сжатия разных частей цельного файла, если можно использовать обычную функцию "ZSTD_compress" для пришедшей очередной части файла и результат просто добавлять в буффер результата, как это и делает функция  "Zstd__SimpleCompress/Zstd__SimpleCompress_CCtx" - единсвенно, что функция "Zstd__SimpleCompress/Zstd__SimpleCompress_CCtx" не подходит для разбития буффера на Чанки при сжатии, НО если разбивать на Чанки не нужно, тогда смысл специальной потоковй функции - не понятен мне.

	

	Zstd__Stream__KnownFinalSize Zstd__Stream__KnownFinalSize_;

	//Методы:
	//- run_StartStream
	//- run_ContinueStream
	//- set__StreamEnd
	//- run_Uncompress
	//- set__param_Сompress
	//- ResetContext_Uncompress
	//- set__param_Uncompress
	//- ResetContext_Сompress



	std::string balvanka_2_1 = "Hello1_Hello2_Hello3_Hello4_Hello5_Hello6_Hello7_Hello8_Hello9_Hello10!!!";
	std::string balvanka_2_2 = "Buy1_Buy2_Buy3_Buy4_Buy5_Buy6_Buy7_Buy8_Buy9_Buy10xxx";


	Zstd__Stream__KnownFinalSize::result_flag result_2;



	//--------------------------------------------------------------------------------------------run_StartStream, run_ContinueStream, set__StreamEnd:Начало---------------------------------------------------------------------------------------------------------
	
	//Функция сжимает данные в потоковом режиме с возможность сжатия предоставленного буффера данных по частям.


	//-------------------------------------------------------------------------------------------------
	const int numm_thread_2_1 = 0;                                               //Кол-во потоков процессора, который задействуется при сжатыи: 0 - Однопоточный режим.[Для задействования многопоточности должен быть опредлен define "ZSTD_MULTITHREAD"]

	const int level_compressed_2_1 = 21;                                         //Уровень сжатия: от 0 до 22. 0 - без сжатия ... 22 - масимальное сжатые.

	const size_t Finaly_size_2 = balvanka_2_1.size() + balvanka_2_2.size();      //Итоговый размер всего "файла"
		
	const size_t chunk_size_2_1 = 200;                                           //Размер в байтах части, которая будет считыватся из буффера с данными которые нужно сжать и эту считанную часть сжимать.Если делить на части буффер по указателю "char_p__to_data_should_be_compressed_7" и нужно сжать его, один куском, то просто указать размер буффера по этому указателю, то есть "size__data_to_be_compressed_7".

	const char* char_p__to_data_should_be_compressed_2_1 = &balvanka_2_1[0];     //Указатель на данные, которые нужно Сжать. Первая часть.

	size_t size__data_to_be_compressed_2_1 = balvanka_2_1.size();                //Размер данных, который должен быть Сжат.

	Zstd__Stream__KnownFinalSize::Stream_flag Stream_flag_2_1 = Zstd__Stream__KnownFinalSize::Stream_flag::continue_stream;     //Флаг состояния потока, читать Три читуации чуть ниже.


	std::string string_compressed_result_2_1;                                  //Сюда в случае успеха - функция добавит в конец сжатые данные в соотвествии с установленными парамтерами. В случае ошибки, память будет возвращена к тому значению, которое было до вызова функии.
	//-------------------------------------------------------------------------------------------------




	//------------------------------------------------------------------------------------------
	//ВАЖНО, КАК ЗАПУСКАТЬ функии "run_xxx": примечаение: РАЗМЕР ВСЕГО ЦЕЛЬНОГО ФАЙЛА, ТО ЕСТЬ СУММА РАЗМЕРОВ ВСЕХ ЧАСТЕЙ ДОЛЖНА БЫТЬ ИЗВЕСТНА ЗАРАНЕЕ И УКАЗАНА ПРИ ПЕРВОМ ВЫЗОВЕ.
	//1-ситуация: предположим условно что с сети пришла часть файла, то есть просто массив данных известного размера и вызываем "run_StartStream" с флагом Stream_flag::continue_stream, теперь приходить вторая часть, НЕ Последняя из этого файла, вызываем "run_ContinueStream" также с флагом Stream_flag::continue_stream, а теперь приходить тридцать вторая часть этого файла последняя, то есть эта часть завершающая часть этого файла, то для вызывается "run_ContinueStream" с флагом Stream_flag::end_stream.
	//2-ситуация: предположим условно что с сети пришла часть файла, то есть просто массив данных известного размера и точно известно, что это первая и последняя часть целого файла, то вызываем "run_StartStream" с флагом Stream_flag::end_stream.
	//3-Ситуация: предположим условно что с сети пришла часть файла, то есть просто массив данных известного размера и на момент вызова "run_StartStream" с флагом Stream_flag::continue_stream - было не изветсно, что эта был последняя часть файла, а стал известно уже после вызова "run_StartStream", то потом просто нужно вызвать метод "set__StreamEnd()"

	
	result_2 = Zstd__Stream__KnownFinalSize_.run_StartStream(numm_thread_2_1, level_compressed_2_1, Finaly_size_2, chunk_size_2_1, char_p__to_data_should_be_compressed_2_1, size__data_to_be_compressed_2_1, string_compressed_result_2_1, Stream_flag_2_1);

	//result_2 = Zstd__Stream__KnownFinalSize_.run_ContinueStream(chunk_size_2_1, char_p__to_data_should_be_compressed_2_1, size__data_to_be_compressed_2_1, string_compressed_result_2_1, Stream_flag_2_1);

	//result_2 = Zstd__Stream__KnownFinalSize_.set__StreamEnd();  //3-Ситуация


	if (result_2 != Zstd__Stream__KnownFinalSize::result_flag::OK)
	{
		std::cout << "Error_2:" << Zstd__Stream__KnownFinalSize_.get__ErrorName() << std::endl;

		return -1;
	}
	else
	{
		std::cout << "string_compressed_result_2_1:" << string_compressed_result_2_1 << std::endl;
	}
	//------------------------------------------------------------------------------------------





	//------------------------------------------------------------------------------------------
	result_2 = Zstd__Stream__KnownFinalSize_.run_ContinueStream(20, &balvanka_2_2[0], balvanka_2_2.size(), string_compressed_result_2_1, Zstd__Stream__KnownFinalSize::Stream_flag::end_stream);   //Ставим флаг "конца потока", так как это последняя часть цельного файла.


	if (result_2 != Zstd__Stream__KnownFinalSize::result_flag::OK)
	{
		std::cout << "Error_2:" << Zstd__Stream__KnownFinalSize_.get__ErrorName() << std::endl;

		return -1;
	}
	else
	{
		std::cout << "string_compressed_result_2_1:" << string_compressed_result_2_1 << std::endl;          //Выводим итоговые сжатые данные.
	}
	//------------------------------------------------------------------------------------------




	//--------------------------------------------------------------------------------------------run_StartStream, run_ContinueStream, set__StreamEnd:Конец---------------------------------------------------------------------------------------------------------





	//-------------------------------------------------------------------------------------------------------------run_Uncompress:Начало---------------------------------------------------------------------------------------------------------

	//Функция расжимает ранее сжатые пооковые данные.

	//--------------------------------------------------------------------------
	const size_t chunk_size_2_2 = 2;                                                                           //Размер Чанка в байтах, то есть функция будет расжимать данные по указателю "char_p__to_uncompressed_data_2_1" по частям. ЕСЛИ расжимать частями сжатые данные не нужно, то просто указать размер Чанка равному размеру самиx сжатых данных.

	const char* char_p__to_uncompressed_data_2_1 = &string_compressed_result_2_1[0];                             //Указатель на Сжатые данные, которые нужно разжать.

	const size_t size__uncompressed_data_2_1     = string_compressed_result_2_1.size();                          //Размер Сжатых данных, которые нужно разжать.


	std::string result_Uncumpress_2_1;                                                                          //Сюда функция в конец добавит расжатые данные.
	//--------------------------------------------------------------------------


	//result_Uncumpress_2_1.resize(0);        //Так как функция добавляет Разжатые данные в конец переданного обьекта строки, то если там уже есть какие то данные, а записать нужно к примеру с начала, то перед вызвом функции нужно обнулить, если нужно чтобы в строке шли подряд два Фрейма сжатых данных, то менять размер соовтетвенно не нужно.

	result_2 = Zstd__Stream__KnownFinalSize_.run_Uncompress(chunk_size_2_2, char_p__to_uncompressed_data_2_1, size__uncompressed_data_2_1, result_Uncumpress_2_1);


	if (result_2 != Zstd__Stream__KnownFinalSize::result_flag::OK)
	{
		std::cout << "Error_2:" << Zstd__Stream__KnownFinalSize_.get__ErrorName() << std::endl;

		return -1;
	}
	else
	{
		std::cout << "result_Uncumpress_2_1:" << result_Uncumpress_2_1 << std::endl;             //Выводим рахжатые данные.
	}

	//-------------------------------------------------------------------------------------------------------------run_Uncompress:Начало---------------------------------------------------------------------------------------------------------










	//--------------------------------------------------------------------------set__param_Сompress:Начало---------------------------------------------------------------------------

	//Данная фукнция вызывает внутри "ZSTD_CCtx_setParameter" устанавливая дополнительно настраиваемые параметры сжатия.

		//---------------------------------------------------
		//Параметры и их описания, которые принимает функция ZSTD_CCtx_setParameter можно найти или в документации на странице: https://facebook.github.io/zstd/zstd_manual.html   - смотреть enum ZSTD_cParameter.
		//Или в исxодном файле zstd.h - смотреть тот же enum ZSTD_cParameter.

		//ZSTD_cParam_getBounds - данная функция принимает один из параметров "ZSTD_cParameter" и возвращает его минимальное и максимальное значение, которое предается в функцию "ZSTD_CCtx_setParameter" третьим "param_value" параметром.
		//ZSTD_bounds ZSTD_bounds_1 = ZSTD_cParam_getBounds(ZSTD_c_nbWorkers);
		//std::cout << "минимальные значение параметра:" << ZSTD_bounds_1.lowerBound << std::endl;
		//std::cout << "максимальное значение параметра:" << ZSTD_bounds_1.upperBound << std::endl;

		//Проверку на ошибку после вызова через  ZSTD_isError.
		//---------------------------------------------------



	//------------------------------------------------------------------------------------

	const ZSTD_cParameter param_2с = ZSTD_c_minMatch;  //Какой то один из параметров.
	const int param_value_2с = ZSTD_cParam_getBounds(param_2с).lowerBound;

	result_2 = Zstd__Stream__KnownFinalSize_.set__param_Compress(param_2с, param_value_2с);


	//------------------------------------------------------------------------------------------
	if (result_2 != Zstd__Stream__KnownFinalSize::result_flag::OK)
	{
		std::cout << "error_2:" << Zstd__Stream__KnownFinalSize_.get__ErrorName() << std::endl;

		return -1;
	}

	//------------------------------------------------------------------------------------


	//--------------------------------------------------------------------------set__param_Сompress:Начало---------------------------------------------------------------------------




	//--------------------------------------------------------------------------set__param_Uncompress:Начало---------------------------------------------------------------------------

	//Данная фукнция вызывает внутри "ZSTD_DCtx_setParameter" устанавливая дополнительно настраиваемые параметры дэкомпрессии.

		//---------------------------------------------------
		//Параметры и их описание, которые принимает функция ZSTD_DCtx_setParameter можно найти или в документации на странице: https://facebook.github.io/zstd/zstd_manual.html   - смотреть enum ZSTD_dParameter.
		//Или в исxодном файле zstd.h - смотреть тот же enum ZSTD_dParameter.


		//ZSTD_dParam_getBounds - данная функция принимает один из параметров "ZSTD_dParameter" и возвращает его минимальное и максимальное значение, которое предается в функцию "ZSTD_DCtx_setParameter" третьим "param_value" параметром.
		//ZSTD_bounds ZSTD_bounds_1 = ZSTD_dParam_getBounds(ZSTD_d_windowLogMax);
		//std::cout << "минимальные значение параметра:" << ZSTD_bounds_1.lowerBound << std::endl;
		//std::cout << "максимальное значение параметра:" << ZSTD_bounds_1.upperBound << std::endl;

		//Проверку на ошибку после вызова через ZSTD_isError.

		//---------------------------------------------------




	//------------------------------------------------------------------------------------
	const ZSTD_dParameter param_2d = ZSTD_d_windowLogMax;  //Какой то один из параметров.
	const int param_value_2d = ZSTD_dParam_getBounds(param_2d).lowerBound;

	result_2 = Zstd__Stream__KnownFinalSize_.set__param_Uncompress(param_2d, param_value_2d);


	//------------------------------------------------------------------------------------------
	if (result_2 != Zstd__Stream__KnownFinalSize::result_flag::OK)
	{
		std::cout << "error_2:" << Zstd__Stream__KnownFinalSize_.get__ErrorName() << std::endl;

		return -1;
	}

	//------------------------------------------------------------------------------------



	//--------------------------------------------------------------------------set__param_Uncompress:Конец---------------------------------------------------------------------------




	//--------------------------------------------------------------------------------ResetContext_Compress:Начало--------------------------------------------------------------------------------------

	//Вообщем данная функция внутри вызывает "ZSTD_CCtx_reset" то есь сбрасывает сосояние контекста дэкомпрессии. Как написано в документации: https://facebook.github.io/zstd/zstd_manual.html

	//Функция принимает тип "ZSTD_ResetDirective" смотреть в файле zstd.h:

	//typedef enum 
	//{
	//	ZSTD_reset_session_only = 1,
	//	ZSTD_reset_parameters = 2,
	//	ZSTD_reset_session_and_parameters = 3
	//} ZSTD_ResetDirective;


	//There are 2 different things that can be reset, independently or jointly : 
	//-ZSTD_reset_session_only:            The session : will stop compressing current frame, and make CCtx ready to start a new one.Useful after an error, or to interrupt any ongoing compression.Any internal data not yet flushed is cancelled.Compression parameters and dictionary remain unchanged.They will be used to compress next frame.Resetting session never fails. 
	//-ZSTD_reset_parameters:              The parameters : changes all parameters back to "default".This removes any reference to any dictionary too.Parameters can only be changed between 2 sessions(i.e.no compression is currently ongoing) otherwise the reset fails, and function returns an error value(which can be tested using ZSTD_isError()) 
	//-ZSTD_reset_session_and_parameters:  Both : similar to resetting the session, followed by resetting parameters.

	//Есть 2 разных параметра, которые можно сбросить, независимо или совместно:
	//-ZSTD_reset_session_only:           Сессия: прекратит сжатие текущего кадра и подготовит CCtx к началу нового. Полезно после ошибки или для прерывания любого текущего сжатия. Любые внутренние данные, которые еще не были сброшены, отменяются. Параметры сжатия и словарь остаются неизменными. Они будут использоваться для сжатия следующего кадра. Сброс сеанса никогда не приводит к сбою.
	//-ZSTD_reset_parameters:             Параметры: изменяют все параметры обратно на «по умолчанию». Это также удаляет любые ссылки на любой словарь. Параметры можно изменять только между 2 сеансами (т. е. в данный момент сжатие не выполняется), в противном случае сброс не выполняется, и функция возвращает значение ошибки (которое можно проверить с помощью ZSTD_isError())
	//-ZSTD_reset_session_and_parameters: Оба: аналогично сбросу сеанса с последующим сбросом параметров.

	//Честно говоря хрен знает на что эти сбросы особо влияют, единсвенно что более менее понятно - это сброc "ZSTD_reset_parameters" - который сбрасывает все ранее дополнительно установленные параметры с помощью функции "set__param" - в состояние по умолчанию - ну так уровень сжатия, уровни скорости сжатия, окно буффера и прочие магические праметры.


	ZSTD_ResetDirective reset_param_2c = ZSTD_reset_parameters;

	result_2 = Zstd__Stream__KnownFinalSize_.ResetContext_Compress(reset_param_2c);


	//------------------------------------------------------------------------------------------
	if (result_2 != Zstd__Stream__KnownFinalSize::result_flag::OK)
	{
		std::cout << "error_2:" << Zstd__Stream__KnownFinalSize_.get__ErrorName() << std::endl;

		return -1;
	}

	//------------------------------------------------------------------------------------


	//--------------------------------------------------------------------------------ResetContext_Compress:Конец--------------------------------------------------------------------------------------






	//--------------------------------------------------------------------------------ResetContext_Uncompress:Начало--------------------------------------------------------------------------------------

	//Вообщем данная функция внутри вызывает "ZSTD_DCtx_reset" то есь сбрасывает сосояние контекста дэкомпрессии. Как написано в документации: https://facebook.github.io/zstd/zstd_manual.html

	//Функция принимает тип "ZSTD_ResetDirective" смотреть в файле zstd.h:

	//typedef enum 
	//{
	//	ZSTD_reset_session_only = 1,
	//	ZSTD_reset_parameters = 2,
	//	ZSTD_reset_session_and_parameters = 3
	//} ZSTD_ResetDirective;


	//There are 2 different things that can be reset, independently or jointly : 
	//-ZSTD_reset_session_only:            The session : will stop compressing current frame, and make CCtx ready to start a new one.Useful after an error, or to interrupt any ongoing compression.Any internal data not yet flushed is cancelled.Compression parameters and dictionary remain unchanged.They will be used to compress next frame.Resetting session never fails. 
	//-ZSTD_reset_parameters:              The parameters : changes all parameters back to "default".This removes any reference to any dictionary too.Parameters can only be changed between 2 sessions(i.e.no compression is currently ongoing) otherwise the reset fails, and function returns an error value(which can be tested using ZSTD_isError()) 
	//-ZSTD_reset_session_and_parameters:  Both : similar to resetting the session, followed by resetting parameters.

	//Есть 2 разных параметра, которые можно сбросить, независимо или совместно:
	//-ZSTD_reset_session_only:           Сессия: прекратит сжатие текущего кадра и подготовит CCtx к началу нового. Полезно после ошибки или для прерывания любого текущего сжатия. Любые внутренние данные, которые еще не были сброшены, отменяются. Параметры сжатия и словарь остаются неизменными. Они будут использоваться для сжатия следующего кадра. Сброс сеанса никогда не приводит к сбою.
	//-ZSTD_reset_parameters:             Параметры: изменяют все параметры обратно на «по умолчанию». Это также удаляет любые ссылки на любой словарь. Параметры можно изменять только между 2 сеансами (т. е. в данный момент сжатие не выполняется), в противном случае сброс не выполняется, и функция возвращает значение ошибки (которое можно проверить с помощью ZSTD_isError())
	//-ZSTD_reset_session_and_parameters: Оба: аналогично сбросу сеанса с последующим сбросом параметров.

	//Честно говоря хрен знает на что эти сбросы особо влияют, единсвенно что более менее понятно - это сброc "ZSTD_reset_parameters" - который сбрасывает все ранее дополнительно установленные параметры с помощью функции "set__param" - в состояние по умолчанию - ну так уровень сжатия, уровни скорости сжатия, окно буффера и прочие магические праметры.


	ZSTD_ResetDirective reset_param_2d = ZSTD_reset_parameters;

	result_2 = Zstd__Stream__KnownFinalSize_.ResetContext_Uncompress(reset_param_2d);


	//------------------------------------------------------------------------------------------
	if (result_2 != Zstd__Stream__KnownFinalSize::result_flag::OK)
	{
		std::cout << "error_2:" << Zstd__Stream__KnownFinalSize_.get__ErrorName() << std::endl;

		return -1;
	}

	//------------------------------------------------------------------------------------


	//--------------------------------------------------------------------------------ResetContext_Uncompress:Конец--------------------------------------------------------------------------------------




	//************************************************************************************2-Zstd__Stream__KnownFinalSize:Конец************************************************************************************









	//************************************************************************************3-Zstd__Stream__UnknownFinalSize:Начало************************************************************************************
	//Данная функция сжимает "потоковые данные" целевого "файла" по частям: размер всего итогового "файла" указывать не нужно.
	//Важно: Сжатие по частям, когда часть меньше размера самого буффера с данными - естесвенно менее эффективно по итогвому результату, если бы сжатие происходило бы всего буффера с входящими данными.
	//БОЛЕЕ ПОДРОБНО: предположим условно что с сети пришла часть файла, то есть просто массив данных известного размера, вызываем "run_StartStream" с флагом Stream_flag::continue_stream, теперь приходить вторая часть, НЕ Последняя из этого файла, вызываем "run_ContinueStream" с флагом Stream_flag::continue_stream, а теперь приходить тридцать вторая часть этого файла последняя, то есть эта часть завершающая часть этого файла, то для это части нужно вызвать Stream_flag::end_stream. 
	//ВОПРОС: однако я нифига не понимаю, в чем смысл использовать именно функцию потокового сжатия "ZSTD_compressStream2" для сжатия разных частей цельного файла, если можно использовать обычную функцию "ZSTD_compress" для пришедшей очередной части файла и результат просто добавлять в буффер результата, как это и делает функция  "Zstd__SimpleCompress/Zstd__SimpleCompress_CCtx" - единсвенно, что функция "Zstd__SimpleCompress/Zstd__SimpleCompress_CCtx" не подходит для разбития буффера на Чанки при сжатии, НО если разбивать на Чанки не нужно, тогда смысл специальной потоковй функции - не понятен мне.

	

	Zstd__Stream__UnknownFinalSize Zstd__Stream__UnknownFinalSize_;

	//Методы:
	//- run_StartStream
	//- run_ContinueStream
	//- set__StreamEnd
	//- run_Uncompress
	//- set__param_Сompress
	//- ResetContext_Uncompress
	//- set__param_Uncompress
	//- ResetContext_Сompress



	std::string balvanka_3_1 = "Hello1_Hello2_Hello3_Hello4_Hello5_Hello6_Hello7_Hello8_Hello9_Hello10!!!";
	std::string balvanka_3_2 = "Buy1_Buy2_Buy3_Buy4_Buy5_Buy6_Buy7_Buy8_Buy9_Buy10xxx";


	Zstd__Stream__UnknownFinalSize::result_flag result_3;



	//--------------------------------------------------------------------------------------------run_StartStream, run_ContinueStream, set__StreamEnd:Начало---------------------------------------------------------------------------------------------------------

	//Функция сжимает данные в потоковом режиме с возможность сжатия предоставленного буффера данных по частям.


	//-------------------------------------------------------------------------------------------------
	const int numm_thread_3_1 = 0;                                               //Кол-во потоков процессора, который задействуется при сжатыи: 0 - Однопоточный режим.[Для задействования многопоточности должен быть опредлен define "ZSTD_MULTITHREAD"]

	const int level_compressed_3_1 = 21;                                         //Уровень сжатия: от 0 до 22. 0 - без сжатия ... 22 - масимальное сжатые.

	const size_t chunk_size_3_1 = 1;                                             //Размер в байтах части, которая будет считыватся из буффера с данными которые нужно сжать и эту считанную часть сжимать.Если делить на части буффер по указателю "char_p__to_data_should_be_compressed_7" и нужно сжать его, один куском, то просто указать размер буффера по этому указателю, то есть "size__data_to_be_compressed_7".

	const char* char_p__to_data_should_be_compressed_3_1 = &balvanka_3_1[0];     //Указатель на данные, которые нужно Сжать. Первая часть.

	size_t size__data_to_be_compressed_3_1 = balvanka_3_1.size();                //Размер данных, который должен быть Сжат.

	Zstd__Stream__UnknownFinalSize::Stream_flag Stream_flag_3_1 = Zstd__Stream__UnknownFinalSize::Stream_flag::continue_stream;     //Флаг состояния потока, читать Три читуации чуть ниже.


	std::string string_compressed_result_3_1;                                  //Сюда в случае успеха - функция добавит в конец сжатые данные в соотвествии с установленными парамтерами. В случае ошибки, память будет возвращена к тому значению, которое было до вызова функии.
	//-------------------------------------------------------------------------------------------------



	//------------------------------------------------------------------------------------------
	//ВАЖНО, КАК ЗАПУСКАТЬ функии "run_xxx": 
	//1-ситуация: предположим условно что с сети пришла часть файла, то есть просто массив данных известного размера, вызываем "run_StartStream" с флагом Stream_flag::continue_stream, теперь приходить вторая часть, НЕ Последняя из этого файла, вызываем "run_ContinueStream" также с флагом Stream_flag::continue_stream, а теперь приходить тридцать вторая часть этого файла последняя, то есть эта часть завершающая часть этого файла, то для вызывается "run_ContinueStream" с флагом Stream_flag::end_stream.
	//2-ситуация: предположим условно что с сети пришла часть файла, то есть просто массив данных известного размера и точно известно, что это первая и последняя часть целого файла, то вызываем "run_StartStream" с флагом Stream_flag::end_stream.
	//3-Ситуация: предположим условно что с сети пришла часть файла, то есть просто массив данных известного размера и на момент вызова "run_StartStream" с флагом Stream_flag::continue_stream - было не изветсно, что эта был последняя часть файла, а стал известно уже после вызова "run_StartStream", то потом просто нужно вызвать метод "set__StreamEnd()"


	
	result_3 = Zstd__Stream__UnknownFinalSize_.run_StartStream(numm_thread_3_1, level_compressed_3_1, chunk_size_3_1, char_p__to_data_should_be_compressed_3_1, size__data_to_be_compressed_3_1, string_compressed_result_3_1, Stream_flag_3_1);

	//result_3 = Zstd__Stream__UnknownFinalSize_.run_ContinueStream(chunk_size_3_1, char_p__to_data_should_be_compressed_3_1, size__data_to_be_compressed_3_1, string_compressed_result_3_1, Stream_flag_3_1);

	//result_3 = Zstd__Stream__UnknownFinalSize_.set__StreamEnd();  //3-Ситуация

	
	if (result_3 != Zstd__Stream__UnknownFinalSize::result_flag::OK)
	{
		std::cout << "Error_3:" << Zstd__Stream__UnknownFinalSize_.get__ErrorName() << std::endl;

		return -1;
	}
	else
	{
		std::cout << "string_compressed_result_3_1:" << string_compressed_result_3_1 << std::endl;
	}
	//------------------------------------------------------------------------------------------





	//------------------------------------------------------------------------------------------
	result_3 = Zstd__Stream__UnknownFinalSize_.run_ContinueStream(20, &balvanka_3_2[0], balvanka_3_2.size(), string_compressed_result_3_1, Zstd__Stream__UnknownFinalSize::Stream_flag::end_stream);   //Ставим флаг "конца потока", так как это последняя часть цельного файла.


	if (result_3 != Zstd__Stream__UnknownFinalSize::result_flag::OK)
	{
		std::cout << "Error_3:" << Zstd__Stream__UnknownFinalSize_.get__ErrorName() << std::endl;

		return -1;
	}
	else
	{
		std::cout << "string_compressed_result_3_1:" << string_compressed_result_3_1 << std::endl;          //Выводим итоговые сжатые данные.
	}
	//------------------------------------------------------------------------------------------




	//--------------------------------------------------------------------------------------------run_StartStream, run_ContinueStream, set__StreamEnd:Конец---------------------------------------------------------------------------------------------------------





	//-------------------------------------------------------------------------------------------------------------run_Uncompress:Начало---------------------------------------------------------------------------------------------------------

	//Функция расжимает ранее сжатые пооковые данные.

	//--------------------------------------------------------------------------
	const size_t chunk_size_3_2 = 2;                                                                           //Размер Чанка в байтах, то есть функция будет расжимать данные по указателю "char_p__to_uncompressed_data_3_1" по частям. ЕСЛИ расжимать частями сжатые данные не нужно, то просто указать размер Чанка равному размеру самиx сжатых данных.

	const char* char_p__to_uncompressed_data_3_1 = &string_compressed_result_3_1[0];                             //Указатель на Сжатые данные, которые нужно разжать.

	const size_t size__uncompressed_data_3_1 = string_compressed_result_3_1.size();                          //Размер Сжатых данных, которые нужно разжать.


	std::string result_Uncumpress_3_1;                                                                          //Сюда функция в конец добавит расжатые данные.
	//--------------------------------------------------------------------------


	//result_Uncumpress_3_1.resize(0);        //Так как функция добавляет Разжатые данные в конец переданного обьекта строки, то если там уже есть какие то данные, а записать нужно к примеру с начала, то перед вызвом функции нужно обнулить, если нужно чтобы в строке шли подряд два Фрейма сжатых данных, то менять размер соовтетвенно не нужно.

	result_3 = Zstd__Stream__UnknownFinalSize_.run_Uncompress(chunk_size_3_2, char_p__to_uncompressed_data_3_1, size__uncompressed_data_3_1, result_Uncumpress_3_1);


	if (result_3 != Zstd__Stream__UnknownFinalSize::result_flag::OK)
	{
		std::cout << "Error_3:" << Zstd__Stream__UnknownFinalSize_.get__ErrorName() << std::endl;

		return -1;
	}
	else
	{
		std::cout << "result_Uncumpress_3_1:" << result_Uncumpress_3_1 << std::endl;             //Выводим рахжатые данные.
	}

	//-------------------------------------------------------------------------------------------------------------run_Uncompress:Начало---------------------------------------------------------------------------------------------------------










	//--------------------------------------------------------------------------set__param_Сompress:Начало---------------------------------------------------------------------------

	//Данная фукнция вызывает внутри "ZSTD_CCtx_setParameter" устанавливая дополнительно настраиваемые параметры сжатия.

		//---------------------------------------------------
		//Параметры и их описания, которые принимает функция ZSTD_CCtx_setParameter можно найти или в документации на странице: https://facebook.github.io/zstd/zstd_manual.html   - смотреть enum ZSTD_cParameter.
		//Или в исxодном файле zstd.h - смотреть тот же enum ZSTD_cParameter.

		//ZSTD_cParam_getBounds - данная функция принимает один из параметров "ZSTD_cParameter" и возвращает его минимальное и максимальное значение, которое предается в функцию "ZSTD_CCtx_setParameter" третьим "param_value" параметром.
		//ZSTD_bounds ZSTD_bounds_1 = ZSTD_cParam_getBounds(ZSTD_c_nbWorkers);
		//std::cout << "минимальные значение параметра:" << ZSTD_bounds_1.lowerBound << std::endl;
		//std::cout << "максимальное значение параметра:" << ZSTD_bounds_1.upperBound << std::endl;

		//Проверку на ошибку после вызова через  ZSTD_isError.
		//---------------------------------------------------



	//------------------------------------------------------------------------------------

	const ZSTD_cParameter param_3с = ZSTD_c_minMatch;  //Какой то один из параметров.
	const int param_value_3с = ZSTD_cParam_getBounds(param_3с).lowerBound;

	result_3 = Zstd__Stream__UnknownFinalSize_.set__param_Compress(param_3с, param_value_3с);


	//------------------------------------------------------------------------------------------
	if (result_3 != Zstd__Stream__UnknownFinalSize::result_flag::OK)
	{
		std::cout << "error_3:" << Zstd__Stream__UnknownFinalSize_.get__ErrorName() << std::endl;

		return -1;
	}

	//------------------------------------------------------------------------------------


	//--------------------------------------------------------------------------set__param_Сompress:Начало---------------------------------------------------------------------------




	//--------------------------------------------------------------------------set__param_Uncompress:Начало---------------------------------------------------------------------------

	//Данная фукнция вызывает внутри "ZSTD_DCtx_setParameter" устанавливая дополнительно настраиваемые параметры дэкомпрессии.

		//---------------------------------------------------
		//Параметры и их описание, которые принимает функция ZSTD_DCtx_setParameter можно найти или в документации на странице: https://facebook.github.io/zstd/zstd_manual.html   - смотреть enum ZSTD_dParameter.
		//Или в исxодном файле zstd.h - смотреть тот же enum ZSTD_dParameter.


		//ZSTD_dParam_getBounds - данная функция принимает один из параметров "ZSTD_dParameter" и возвращает его минимальное и максимальное значение, которое предается в функцию "ZSTD_DCtx_setParameter" третьим "param_value" параметром.
		//ZSTD_bounds ZSTD_bounds_1 = ZSTD_dParam_getBounds(ZSTD_d_windowLogMax);
		//std::cout << "минимальные значение параметра:" << ZSTD_bounds_1.lowerBound << std::endl;
		//std::cout << "максимальное значение параметра:" << ZSTD_bounds_1.upperBound << std::endl;

		//Проверку на ошибку после вызова через ZSTD_isError.

		//---------------------------------------------------




	//------------------------------------------------------------------------------------
	const ZSTD_dParameter param_3d = ZSTD_d_windowLogMax;  //Какой то один из параметров.
	const int param_value_3d = ZSTD_dParam_getBounds(param_3d).lowerBound;

	result_3 = Zstd__Stream__UnknownFinalSize_.set__param_Uncompress(param_3d, param_value_3d);


	//------------------------------------------------------------------------------------------
	if (result_3 != Zstd__Stream__UnknownFinalSize::result_flag::OK)
	{
		std::cout << "error_3:" << Zstd__Stream__UnknownFinalSize_.get__ErrorName() << std::endl;

		return -1;
	}

	//------------------------------------------------------------------------------------



	//--------------------------------------------------------------------------set__param_Uncompress:Конец---------------------------------------------------------------------------




	//--------------------------------------------------------------------------------ResetContext_Compress:Начало--------------------------------------------------------------------------------------

	//Вообщем данная функция внутри вызывает "ZSTD_CCtx_reset" то есь сбрасывает сосояние контекста дэкомпрессии. Как написано в документации: https://facebook.github.io/zstd/zstd_manual.html

	//Функция принимает тип "ZSTD_ResetDirective" смотреть в файле zstd.h:

	//typedef enum 
	//{
	//	ZSTD_reset_session_only = 1,
	//	ZSTD_reset_parameters = 2,
	//	ZSTD_reset_session_and_parameters = 3
	//} ZSTD_ResetDirective;


	//There are 2 different things that can be reset, independently or jointly : 
	//-ZSTD_reset_session_only:            The session : will stop compressing current frame, and make CCtx ready to start a new one.Useful after an error, or to interrupt any ongoing compression.Any internal data not yet flushed is cancelled.Compression parameters and dictionary remain unchanged.They will be used to compress next frame.Resetting session never fails. 
	//-ZSTD_reset_parameters:              The parameters : changes all parameters back to "default".This removes any reference to any dictionary too.Parameters can only be changed between 2 sessions(i.e.no compression is currently ongoing) otherwise the reset fails, and function returns an error value(which can be tested using ZSTD_isError()) 
	//-ZSTD_reset_session_and_parameters:  Both : similar to resetting the session, followed by resetting parameters.

	//Есть 2 разных параметра, которые можно сбросить, независимо или совместно:
	//-ZSTD_reset_session_only:           Сессия: прекратит сжатие текущего кадра и подготовит CCtx к началу нового. Полезно после ошибки или для прерывания любого текущего сжатия. Любые внутренние данные, которые еще не были сброшены, отменяются. Параметры сжатия и словарь остаются неизменными. Они будут использоваться для сжатия следующего кадра. Сброс сеанса никогда не приводит к сбою.
	//-ZSTD_reset_parameters:             Параметры: изменяют все параметры обратно на «по умолчанию». Это также удаляет любые ссылки на любой словарь. Параметры можно изменять только между 2 сеансами (т. е. в данный момент сжатие не выполняется), в противном случае сброс не выполняется, и функция возвращает значение ошибки (которое можно проверить с помощью ZSTD_isError())
	//-ZSTD_reset_session_and_parameters: Оба: аналогично сбросу сеанса с последующим сбросом параметров.

	//Честно говоря хрен знает на что эти сбросы особо влияют, единсвенно что более менее понятно - это сброc "ZSTD_reset_parameters" - который сбрасывает все ранее дополнительно установленные параметры с помощью функции "set__param" - в состояние по умолчанию - ну так уровень сжатия, уровни скорости сжатия, окно буффера и прочие магические праметры.


	ZSTD_ResetDirective reset_param_3c = ZSTD_reset_parameters;

	result_3 = Zstd__Stream__UnknownFinalSize_.ResetContext_Compress(reset_param_3c);


	//------------------------------------------------------------------------------------------
	if (result_3 != Zstd__Stream__UnknownFinalSize::result_flag::OK)
	{
		std::cout << "error_3:" << Zstd__Stream__UnknownFinalSize_.get__ErrorName() << std::endl;

		return -1;
	}

	//------------------------------------------------------------------------------------


	//--------------------------------------------------------------------------------ResetContext_Compress:Конец--------------------------------------------------------------------------------------






	//--------------------------------------------------------------------------------ResetContext_Uncompress:Начало--------------------------------------------------------------------------------------

	//Вообщем данная функция внутри вызывает "ZSTD_DCtx_reset" то есь сбрасывает сосояние контекста дэкомпрессии. Как написано в документации: https://facebook.github.io/zstd/zstd_manual.html

	//Функция принимает тип "ZSTD_ResetDirective" смотреть в файле zstd.h:

	//typedef enum 
	//{
	//	ZSTD_reset_session_only = 1,
	//	ZSTD_reset_parameters = 2,
	//	ZSTD_reset_session_and_parameters = 3
	//} ZSTD_ResetDirective;


	//There are 2 different things that can be reset, independently or jointly : 
	//-ZSTD_reset_session_only:            The session : will stop compressing current frame, and make CCtx ready to start a new one.Useful after an error, or to interrupt any ongoing compression.Any internal data not yet flushed is cancelled.Compression parameters and dictionary remain unchanged.They will be used to compress next frame.Resetting session never fails. 
	//-ZSTD_reset_parameters:              The parameters : changes all parameters back to "default".This removes any reference to any dictionary too.Parameters can only be changed between 2 sessions(i.e.no compression is currently ongoing) otherwise the reset fails, and function returns an error value(which can be tested using ZSTD_isError()) 
	//-ZSTD_reset_session_and_parameters:  Both : similar to resetting the session, followed by resetting parameters.

	//Есть 2 разных параметра, которые можно сбросить, независимо или совместно:
	//-ZSTD_reset_session_only:           Сессия: прекратит сжатие текущего кадра и подготовит CCtx к началу нового. Полезно после ошибки или для прерывания любого текущего сжатия. Любые внутренние данные, которые еще не были сброшены, отменяются. Параметры сжатия и словарь остаются неизменными. Они будут использоваться для сжатия следующего кадра. Сброс сеанса никогда не приводит к сбою.
	//-ZSTD_reset_parameters:             Параметры: изменяют все параметры обратно на «по умолчанию». Это также удаляет любые ссылки на любой словарь. Параметры можно изменять только между 2 сеансами (т. е. в данный момент сжатие не выполняется), в противном случае сброс не выполняется, и функция возвращает значение ошибки (которое можно проверить с помощью ZSTD_isError())
	//-ZSTD_reset_session_and_parameters: Оба: аналогично сбросу сеанса с последующим сбросом параметров.

	//Честно говоря хрен знает на что эти сбросы особо влияют, единсвенно что более менее понятно - это сброc "ZSTD_reset_parameters" - который сбрасывает все ранее дополнительно установленные параметры с помощью функции "set__param" - в состояние по умолчанию - ну так уровень сжатия, уровни скорости сжатия, окно буффера и прочие магические праметры.


	ZSTD_ResetDirective reset_param_3d = ZSTD_reset_parameters;

	result_3 = Zstd__Stream__UnknownFinalSize_.ResetContext_Uncompress(reset_param_3d);


	//------------------------------------------------------------------------------------------
	if (result_3 != Zstd__Stream__UnknownFinalSize::result_flag::OK)
	{
		std::cout << "error_3:" << Zstd__Stream__UnknownFinalSize_.get__ErrorName() << std::endl;

		return -1;
	}

	//------------------------------------------------------------------------------------


	//--------------------------------------------------------------------------------ResetContext_Uncompress:Конец--------------------------------------------------------------------------------------


	//************************************************************************************3-Zstd__Stream__UnknownFinalSize:Конец************************************************************************************











	//************************************************************************************4-Zstd__Stream__Lambda__KnownFinalSize:Начало************************************************************************************
	//Данная функция сжимает "потоковые данные" целевого "файла" по частям: размер всего итогового "файла" нужно знать и указывать заранее. Отличие от "Zstd__Stream__KnownFinalSize" в дополнительном колбеке, который будет вызываться каждый раз для каждого сжимаемого-разжимаемого чанка.
	//Важно: Сжатие по частям, когда часть меньше размера самого буффера с данными - естесвенно менее эффективно по итогвому результату, если бы сжатие происходило бы всего буффера с входящими данными.
	//БОЛЕЕ ПОДРОБНО: предположим условно что с сети пришла часть файла, то есть просто массив данных известного размера, вызываем "run_StartStream" с флагом Stream_flag::continue_stream, теперь приходить вторая часть, НЕ Последняя из этого файла, вызываем "run_ContinueStream" с флагом Stream_flag::continue_stream, а теперь приходить тридцать вторая часть этого файла последняя, то есть эта часть завершающая часть этого файла, то для это части нужно вызвать Stream_flag::end_stream. 
	//ВОПРОС: однако я нифига не понимаю, в чем смысл использовать именно функцию потокового сжатия "ZSTD_compressStream2" для сжатия разных частей цельного файла, если можно использовать обычную функцию "ZSTD_compress" для пришедшей очередной части файла и результат просто добавлять в буффер результата, как это и делает функция  "Zstd__SimpleCompress/Zstd__SimpleCompress_CCtx" - единсвенно, что функция "Zstd__SimpleCompress/Zstd__SimpleCompress_CCtx" не подходит для разбития буффера на Чанки при сжатии, НО если разбивать на Чанки не нужно, тогда смысл специальной потоковй функции - не понятен мне.



	Zstd__Stream__Lambda__KnownFinalSize Zstd__Stream__Lambda__KnownFinalSize_;

	//Методы:
	//- run_StartStream
	//- run_ContinueStream
	//- set__StreamEnd
	//- run_Uncompress
	//- set__param_Сompress
	//- ResetContext_Uncompress
	//- set__param_Uncompress
	//- ResetContext_Сompress



	std::string balvanka_4_1 = "Hello1_Hello2_Hello3_Hello4_Hello5_Hello6_Hello7_Hello8_Hello9_Hello10!!!";
	std::string balvanka_4_2 = "Buy1_Buy2_Buy3_Buy4_Buy5_Buy6_Buy7_Buy8_Buy9_Buy10xxx";


	Zstd__Stream__Lambda__KnownFinalSize::result_flag result_4;



	//--------------------------------------------------------------------------------------------run_StartStream, run_ContinueStream, set__StreamEnd:Начало---------------------------------------------------------------------------------------------------------

	//Функция сжимает данные в потоковом режиме с возможность сжатия предоставленного буффера данных по частям.


	//-------------------------------------------------------------------------------------------------
	const int numm_thread_4_1 = 0;                                               //Кол-во потоков процессора, который задействуется при сжатыи: 0 - Однопоточный режим.[Для задействования многопоточности должен быть опредлен define "ZSTD_MULTITHREAD"]

	const int level_compressed_4_1 = 21;                                         //Уровень сжатия: от 0 до 22. 0 - без сжатия ... 22 - масимальное сжатые.

	const size_t Finaly_size_4 = balvanka_4_1.size() + balvanka_4_2.size();      //Итоговый размер всего "файла"

	const size_t chunk_size_4_1 = 10;                                           //Размер в байтах части, которая будет считыватся из буффера с данными которые нужно сжать и эту считанную часть сжимать.Если делить на части буффер по указателю "char_p__to_data_should_be_compressed_7" и нужно сжать его, один куском, то просто указать размер буффера по этому указателю, то есть "size__data_to_be_compressed_7".

	const char* char_p__to_data_should_be_compressed_4_1 = &balvanka_4_1[0];     //Указатель на данные, которые нужно Сжать. Первая часть.

	size_t size__data_to_be_compressed_4_1 = balvanka_4_1.size();                //Размер данных, который должен быть Сжат.

	Zstd__Stream__Lambda__KnownFinalSize::Stream_flag Stream_flag_4_1 = Zstd__Stream__Lambda__KnownFinalSize::Stream_flag::continue_stream;     //Флаг состояния потока, читать Три читуации чуть ниже.
	//-------------------------------------------------------------------------------------------------


	//-------------------------------------------------------------------------------------------------
	std::string resultos_4c;
	std::function<void(const Zstd__Stream__Lambda__KnownFinalSize::callback_flag status, const char* Pointer_to_ChunkBeforeCompressData, const size_t ChunkBeforeCompressData_size, const char* Pointer_to_ChunkCompressData, const size_t ChunkCompressData_size, const size_t approximate_MaxSize_for_CompressedResult, Zstd__Stream__Lambda__KnownFinalSize* Zstd__Stream_p)> lambda_callback_4c = [&resultos_4c](const Zstd__Stream__Lambda__KnownFinalSize::callback_flag status, const char* Pointer_to_ChunkBeforeCompressData, const size_t ChunkBeforeCompressData_size, const char* Pointer_to_ChunkCompressData, const size_t ChunkCompressData_size, const size_t garant_MaxSize_for_CompressedResult, Zstd__Stream__Lambda__KnownFinalSize* Zstd__Stream_p)
		{


			//------------------------------------------------------------------------------------------------------
			if (status == Zstd__Stream__Lambda__KnownFinalSize::callback_flag::data_chunk)
			{
				//ЗНАЧИТ что: данные на которые указывает:
				//"Pointer_to_ChunkBeforeCompressData" в кол-ве "ChunkBeforeCompressData_size"   - это очередная часть данных, из предсотавленного при вызове функции "run" указателя на буффер с данными которого нужно сжать. 
				//"ChunkBeforeCompressData_size"                                                 - это размер Чанка указанный ранее при вызове функции "run", НО может быть и меньше, если колбек вызвался для "хвоста".
				//"Pointer_to_ChunkCompressData"                                                 - указатель на сжатые данные размером "Pointer_to_ChunkCompressData", которые сжались из несжатых данных по указателю "Pointer_to_ChunkBeforeCompressData"
				//"Zstd__Stream_p"                                                  - указатель на класс, который вызвал данный колбек. Нафиг он нужен, да особо и не нужен, так просто на всякий случай.

				std::cout << Zstd__Stream_p->get__CallbackFlag_Name(status) << std::endl;

				std::string string_temp; string_temp.append(Pointer_to_ChunkCompressData, ChunkCompressData_size);  //Не факт, что "Pointer_to_ChunkCompressData" оканчивается нулем, поэтому скопируем ровно указанное кол-во, чтобы не выводить мусор.

				std::cout << "Pointer_to_ChunkCompressData:" << string_temp << std::endl;
			}

			if (status == Zstd__Stream__Lambda__KnownFinalSize::callback_flag::ending_chunk)
			{
				//Значит это завершающий этап сжатия, функция еще выдает данные, но это уже не полезные данные сжатия, а какая то служеюная информация, которую естесвенно также нужно запиисывать в общией результативный буффер.

				std::cout << Zstd__Stream_p->get__CallbackFlag_Name(status) << std::endl;

				std::string string_temp; string_temp.append(Pointer_to_ChunkCompressData, ChunkCompressData_size);  //Не факт, что "Pointer_to_ChunkCompressData" оканчивается нулем, поэтому скопируем ровно указанное кол-во, чтобы не выводить мусор.

				std::cout << "Pointer_to_ChunkCompressData:" << string_temp << std::endl;
			}

			if (status == Zstd__Stream__Lambda__KnownFinalSize::callback_flag::compression_completed)
			{
				//Это просто информионный кол-бек, который говорит, что все данные сжаты и сжатие завершено. Все указатели и размеры на данные - НЕ ДЕЙСТВИТЕЛЬНЫ.

				std::cout << Zstd__Stream_p->get__CallbackFlag_Name(status) << std::endl;
			}
			//------------------------------------------------------------------------------------------------------

			//------------------------------------------------------------------------------------------------------
			//approximate_MaxSize_for_CompressedResult - Это ПРИМЕРНЫЙ максимальный размер под все части данного вызова "run". ЕЩЕ РАЗ это ПРИМЕРНЫЙ "МАКСИМАЛЬНЫЙ" РАЗМЕР, размер может оказатся и больше и даже меньше. АКТУАЛЕН ТОЛЬКО ВО ВРЕМЯ ПЕРВОГО ВЫЗОВА ДАННОГО КОЛБЕКА, после очередного вызова метода "run" у класса.
			//------------------------------------------------------------------------------------------------------



			//---------------------------------------Добавляем данные в единый буффер:---------------------------------
			resultos_4c.append(Pointer_to_ChunkCompressData, ChunkCompressData_size);
			//-----------------------------------------------------------------------------

		};

	Zstd__Stream__Lambda__KnownFinalSize_.set__LambdaCallback(lambda_callback_4c);  //Устанавливаем лямбду-колбек, который будет вызыватся каждый раз, как функция сожмет очередной Чанк. Установить требутся ДО первого вызовая "run" и только один раз. Если после установки нужно будет заменить дургим колбеком, меняем в любое необходимое время.
	//-------------------------------------------------------------------------------------------------



	
	//------------------------------------------------------------------------------------------
	//ВАЖНО, КАК ЗАПУСКАТЬ функии "run_xxx": примечаение: РАЗМЕР ВСЕГО ЦЕЛЬНОГО ФАЙЛА, ТО ЕСТЬ СУММА РАЗМЕРОВ ВСЕХ ЧАСТЕЙ ДОЛЖНА БЫТЬ ИЗВЕСТНА ЗАРАНЕЕ И УКАЗАНА ПРИ ПЕРВОМ ВЫЗОВЕ.
	//1-ситуация: предположим условно что с сети пришла часть файла, то есть просто массив данных известного размера и вызываем "run_StartStream" с флагом Stream_flag::continue_stream, теперь приходить вторая часть, НЕ Последняя из этого файла, вызываем "run_ContinueStream" также с флагом Stream_flag::continue_stream, а теперь приходить тридцать вторая часть этого файла последняя, то есть эта часть завершающая часть этого файла, то для вызывается "run_ContinueStream" с флагом Stream_flag::end_stream.
	//2-ситуация: предположим условно что с сети пришла часть файла, то есть просто массив данных известного размера и точно известно, что это первая и последняя часть целого файла, то вызываем "run_StartStream" с флагом Stream_flag::end_stream.
	//3-Ситуация: предположим условно что с сети пришла часть файла, то есть просто массив данных известного размера и на момент вызова "run_StartStream" с флагом Stream_flag::continue_stream - было не изветсно, что эта был последняя часть файла, а стал известно уже после вызова "run_StartStream", то потом просто нужно вызвать метод "set__StreamEnd()"

	
	result_4 = Zstd__Stream__Lambda__KnownFinalSize_.run_StartStream(numm_thread_4_1, level_compressed_4_1, Finaly_size_4, chunk_size_4_1, char_p__to_data_should_be_compressed_4_1, size__data_to_be_compressed_4_1, Stream_flag_4_1);

	//result_4 = Zstd__Stream__Lambda__KnownFinalSize_.run_ContinueStream(chunk_size_4_1, char_p__to_data_should_be_compressed_4_1, size__data_to_be_compressed_4_1, Stream_flag_4_1);

	//result_4 = Zstd__Stream__Lambda__KnownFinalSize_.set__StreamEnd();  //3-Ситуация


	if (result_4 != Zstd__Stream__Lambda__KnownFinalSize::result_flag::OK)
	{
		std::cout << "Error_4:" << Zstd__Stream__Lambda__KnownFinalSize_.get__ErrorName() << std::endl;

		return -1;
	}
	else
	{
		std::cout << "resultos_4c:" << resultos_4c << std::endl;
	}
	//------------------------------------------------------------------------------------------





	//------------------------------------------------------------------------------------------
	result_4 = Zstd__Stream__Lambda__KnownFinalSize_.run_ContinueStream(20, &balvanka_4_2[0], balvanka_4_2.size(), Zstd__Stream__Lambda__KnownFinalSize::Stream_flag::end_stream);   //Ставим флаг "конца потока", так как это последняя часть цельного файла.


	if (result_4 != Zstd__Stream__Lambda__KnownFinalSize::result_flag::OK)
	{
		std::cout << "Error_4:" << Zstd__Stream__Lambda__KnownFinalSize_.get__ErrorName() << std::endl;

		return -1;
	}
	else
	{
		std::cout << "resultos_4c:" << resultos_4c << std::endl;          //Выводим итоговые сжатые данные.
	}
	//------------------------------------------------------------------------------------------




	//--------------------------------------------------------------------------------------------run_StartStream, run_ContinueStream, set__StreamEnd:Конец---------------------------------------------------------------------------------------------------------





	//-------------------------------------------------------------------------------------------------------------run_Uncompress:Начало---------------------------------------------------------------------------------------------------------

	//Функция расжимает ранее сжатые пооковые данные.

	//--------------------------------------------------------------------------
	const size_t chunk_size_4_2 = 2;                                                                           //Размер Чанка в байтах, то есть функция будет расжимать данные по указателю "char_p__to_uncompressed_data_4_1" по частям. ЕСЛИ расжимать частями сжатые данные не нужно, то просто указать размер Чанка равному размеру самиx сжатых данных.

	const char* char_p__to_uncompressed_data_4_1 = &resultos_4c[0];                                             //Указатель на Сжатые данные, которые нужно разжать.

	const size_t size__uncompressed_data_4_1 = resultos_4c.size();                                              //Размер Сжатых данных, которые нужно разжать.
	
	
	std::string resultos_4d;
	std::function<void(const Zstd__Stream__Lambda__KnownFinalSize::callback_flag status, const char* Pointer_to_ChunkBeforeUncompressData, const size_t ChunkBeforeUncompressData_size, const char* Pointer_to_ChunkUnompressData, const size_t ChunkUncompressData_size, Zstd__Stream__Lambda__KnownFinalSize* Zstd__Stream__Lambda__KnownFinalSize_p)> lambda_callback_4d = [&resultos_4d](const Zstd__Stream__Lambda__KnownFinalSize::callback_flag status, const char* Pointer_to_ChunkBeforeUncompressData, const size_t ChunkBeforeUncompressData_size, const char* Pointer_to_ChunkUnompressData, const size_t ChunkUncompressData_size, Zstd__Stream__Lambda__KnownFinalSize* Zstd__Stream__Lambda__KnownFinalSize_p)
		{


			//------------------------------------------------------------------------------------------------------
			if (status == Zstd__Stream__Lambda__KnownFinalSize::callback_flag::data_chunk)
			{
				//ЗНАЧИТ что: данные на которые указывает:
				//"Pointer_to_ChunkBeforeUncompressData" в кол-ве "ChunkBeforeCompressData_size" - это очередная часть данных, из предсотавленного при вызове функции "run" буффера - то есть данные которого нужно разжать. 
				//"ChunkBeforeUncompressData_size"                                               - это размер Чанка указанный ранее при вызове функции "run", НО может быть меньше, если колбек вызвался для "хвоста".
				//"Pointer_to_ChunkUnompressData"                                                - указатель на разжатые данные размером "ChunkUncompressData_size", которые разжались из сжатых данных по указателю "Pointer_to_ChunkBeforeUncompressData"
				//"Zstd__StreamUncompress_p"                                                - указатель на класс, который вызвал данный колбек. Нафиг он нужен, да особо и не нужен, так просто на всякий случай.

				std::cout << Zstd__Stream__Lambda__KnownFinalSize_p->get__CallbackFlag_Name(status) << std::endl;

				std::string string_temp; string_temp.append(Pointer_to_ChunkUnompressData, ChunkUncompressData_size);  //Не факт, что "Pointer_to_ChunkUnompressData" оканчивается нулем, поэтому скопируем ровно указанное кол-во, чтобы не выводить мусор.

				std::cout << "Pointer_to_ChunkUnompressData:" << string_temp << std::endl;
			}

			if (status == Zstd__Stream__Lambda__KnownFinalSize::callback_flag::decompression_completed)
			{
				//Это просто информионный кол-бек, который говорит, что все данные сжаты и сжатие завершено. Все указатели и размеры на данные - НЕ ДЕЙСТВИТЕЛЬНЫ.

				std::cout << Zstd__Stream__Lambda__KnownFinalSize_p->get__CallbackFlag_Name(status) << std::endl;
			}
			//------------------------------------------------------------------------------------------------------


			//------------------------------------------------------------------------------------------------------
			//garant_MaxSize_for_CompressedResult - Это гарантированный максимальный размер, под ИТОГОВЫЕ сжатые данные - то есть если проссумировать все "ChunkCompressData_size" до последнего вызова данного колбека - сумма будет меньше или равна == garant_MaxSize_for_CompressedResult.
			//------------------------------------------------------------------------------------------------------



			//------------------------------Занесе данные:----------------------------------------------
			resultos_4d.append(Pointer_to_ChunkUnompressData, ChunkUncompressData_size);
			//-----------------------------------------------------------------------------------


		};
	//--------------------------------------------------------------------------



	//-------------------------------------------------------------------------------------------------------------------------
	//result_Uncumpress_4_1.resize(0);        //Так как функция добавляет Разжатые данные в конец переданного обьекта строки, то если там уже есть какие то данные, а записать нужно к примеру с начала, то перед вызвом функции нужно обнулить, если нужно чтобы в строке шли подряд два Фрейма сжатых данных, то менять размер соовтетвенно не нужно.

	result_4 = Zstd__Stream__Lambda__KnownFinalSize_.run_Uncompress(chunk_size_4_2, char_p__to_uncompressed_data_4_1, size__uncompressed_data_4_1, lambda_callback_4d);


	if (result_4 != Zstd__Stream__Lambda__KnownFinalSize::result_flag::OK)
	{
		std::cout << "Error_4:" << Zstd__Stream__Lambda__KnownFinalSize_.get__ErrorName() << std::endl;

		return -1;
	}
	else
	{
		std::cout << "resultos_4d:" << resultos_4d << std::endl;             //Выводим рахжатые данные.
	}
	//-------------------------------------------------------------------------------------------------------------------------


	//-------------------------------------------------------------------------------------------------------------run_Uncompress:Начало---------------------------------------------------------------------------------------------------------










	//--------------------------------------------------------------------------set__param_Сompress:Начало---------------------------------------------------------------------------

	//Данная фукнция вызывает внутри "ZSTD_CCtx_setParameter" устанавливая дополнительно настраиваемые параметры сжатия.

		//---------------------------------------------------
		//Параметры и их описания, которые принимает функция ZSTD_CCtx_setParameter можно найти или в документации на странице: https://facebook.github.io/zstd/zstd_manual.html   - смотреть enum ZSTD_cParameter.
		//Или в исxодном файле zstd.h - смотреть тот же enum ZSTD_cParameter.

		//ZSTD_cParam_getBounds - данная функция принимает один из параметров "ZSTD_cParameter" и возвращает его минимальное и максимальное значение, которое предается в функцию "ZSTD_CCtx_setParameter" третьим "param_value" параметром.
		//ZSTD_bounds ZSTD_bounds_1 = ZSTD_cParam_getBounds(ZSTD_c_nbWorkers);
		//std::cout << "минимальные значение параметра:" << ZSTD_bounds_1.lowerBound << std::endl;
		//std::cout << "максимальное значение параметра:" << ZSTD_bounds_1.upperBound << std::endl;

		//Проверку на ошибку после вызова через  ZSTD_isError.
		//---------------------------------------------------



	//------------------------------------------------------------------------------------

	const ZSTD_cParameter param_4с = ZSTD_c_minMatch;  //Какой то один из параметров.
	const int param_value_4с = ZSTD_cParam_getBounds(param_4с).lowerBound;

	result_4 = Zstd__Stream__Lambda__KnownFinalSize_.set__param_Compress(param_4с, param_value_4с);


	//------------------------------------------------------------------------------------------
	if (result_4 != Zstd__Stream__Lambda__KnownFinalSize::result_flag::OK)
	{
		std::cout << "error_4:" << Zstd__Stream__Lambda__KnownFinalSize_.get__ErrorName() << std::endl;

		return -1;
	}

	//------------------------------------------------------------------------------------


	//--------------------------------------------------------------------------set__param_Сompress:Начало---------------------------------------------------------------------------




	//--------------------------------------------------------------------------set__param_Uncompress:Начало---------------------------------------------------------------------------

	//Данная фукнция вызывает внутри "ZSTD_DCtx_setParameter" устанавливая дополнительно настраиваемые параметры дэкомпрессии.

		//---------------------------------------------------
		//Параметры и их описание, которые принимает функция ZSTD_DCtx_setParameter можно найти или в документации на странице: https://facebook.github.io/zstd/zstd_manual.html   - смотреть enum ZSTD_dParameter.
		//Или в исxодном файле zstd.h - смотреть тот же enum ZSTD_dParameter.


		//ZSTD_dParam_getBounds - данная функция принимает один из параметров "ZSTD_dParameter" и возвращает его минимальное и максимальное значение, которое предается в функцию "ZSTD_DCtx_setParameter" третьим "param_value" параметром.
		//ZSTD_bounds ZSTD_bounds_1 = ZSTD_dParam_getBounds(ZSTD_d_windowLogMax);
		//std::cout << "минимальные значение параметра:" << ZSTD_bounds_1.lowerBound << std::endl;
		//std::cout << "максимальное значение параметра:" << ZSTD_bounds_1.upperBound << std::endl;

		//Проверку на ошибку после вызова через ZSTD_isError.

		//---------------------------------------------------




	//------------------------------------------------------------------------------------
	const ZSTD_dParameter param_4d = ZSTD_d_windowLogMax;  //Какой то один из параметров.
	const int param_value_4d = ZSTD_dParam_getBounds(param_4d).lowerBound;

	result_4 = Zstd__Stream__Lambda__KnownFinalSize_.set__param_Uncompress(param_4d, param_value_4d);


	//------------------------------------------------------------------------------------------
	if (result_4 != Zstd__Stream__Lambda__KnownFinalSize::result_flag::OK)
	{
		std::cout << "error_4:" << Zstd__Stream__Lambda__KnownFinalSize_.get__ErrorName() << std::endl;

		return -1;
	}

	//------------------------------------------------------------------------------------



	//--------------------------------------------------------------------------set__param_Uncompress:Конец---------------------------------------------------------------------------




	//--------------------------------------------------------------------------------ResetContext_Compress:Начало--------------------------------------------------------------------------------------

	//Вообщем данная функция внутри вызывает "ZSTD_CCtx_reset" то есь сбрасывает сосояние контекста дэкомпрессии. Как написано в документации: https://facebook.github.io/zstd/zstd_manual.html

	//Функция принимает тип "ZSTD_ResetDirective" смотреть в файле zstd.h:

	//typedef enum 
	//{
	//	ZSTD_reset_session_only = 1,
	//	ZSTD_reset_parameters = 2,
	//	ZSTD_reset_session_and_parameters = 3
	//} ZSTD_ResetDirective;


	//There are 2 different things that can be reset, independently or jointly : 
	//-ZSTD_reset_session_only:            The session : will stop compressing current frame, and make CCtx ready to start a new one.Useful after an error, or to interrupt any ongoing compression.Any internal data not yet flushed is cancelled.Compression parameters and dictionary remain unchanged.They will be used to compress next frame.Resetting session never fails. 
	//-ZSTD_reset_parameters:              The parameters : changes all parameters back to "default".This removes any reference to any dictionary too.Parameters can only be changed between 2 sessions(i.e.no compression is currently ongoing) otherwise the reset fails, and function returns an error value(which can be tested using ZSTD_isError()) 
	//-ZSTD_reset_session_and_parameters:  Both : similar to resetting the session, followed by resetting parameters.

	//Есть 2 разных параметра, которые можно сбросить, независимо или совместно:
	//-ZSTD_reset_session_only:           Сессия: прекратит сжатие текущего кадра и подготовит CCtx к началу нового. Полезно после ошибки или для прерывания любого текущего сжатия. Любые внутренние данные, которые еще не были сброшены, отменяются. Параметры сжатия и словарь остаются неизменными. Они будут использоваться для сжатия следующего кадра. Сброс сеанса никогда не приводит к сбою.
	//-ZSTD_reset_parameters:             Параметры: изменяют все параметры обратно на «по умолчанию». Это также удаляет любые ссылки на любой словарь. Параметры можно изменять только между 2 сеансами (т. е. в данный момент сжатие не выполняется), в противном случае сброс не выполняется, и функция возвращает значение ошибки (которое можно проверить с помощью ZSTD_isError())
	//-ZSTD_reset_session_and_parameters: Оба: аналогично сбросу сеанса с последующим сбросом параметров.

	//Честно говоря хрен знает на что эти сбросы особо влияют, единсвенно что более менее понятно - это сброc "ZSTD_reset_parameters" - который сбрасывает все ранее дополнительно установленные параметры с помощью функции "set__param" - в состояние по умолчанию - ну так уровень сжатия, уровни скорости сжатия, окно буффера и прочие магические праметры.


	ZSTD_ResetDirective reset_param_4c = ZSTD_reset_parameters;

	result_4 = Zstd__Stream__Lambda__KnownFinalSize_.ResetContext_Compress(reset_param_4c);


	//------------------------------------------------------------------------------------------
	if (result_4 != Zstd__Stream__Lambda__KnownFinalSize::result_flag::OK)
	{
		std::cout << "error_4:" << Zstd__Stream__Lambda__KnownFinalSize_.get__ErrorName() << std::endl;

		return -1;
	}

	//------------------------------------------------------------------------------------


	//--------------------------------------------------------------------------------ResetContext_Compress:Конец--------------------------------------------------------------------------------------






	//--------------------------------------------------------------------------------ResetContext_Uncompress:Начало--------------------------------------------------------------------------------------

	//Вообщем данная функция внутри вызывает "ZSTD_DCtx_reset" то есь сбрасывает сосояние контекста дэкомпрессии. Как написано в документации: https://facebook.github.io/zstd/zstd_manual.html

	//Функция принимает тип "ZSTD_ResetDirective" смотреть в файле zstd.h:

	//typedef enum 
	//{
	//	ZSTD_reset_session_only = 1,
	//	ZSTD_reset_parameters = 2,
	//	ZSTD_reset_session_and_parameters = 3
	//} ZSTD_ResetDirective;


	//There are 2 different things that can be reset, independently or jointly : 
	//-ZSTD_reset_session_only:            The session : will stop compressing current frame, and make CCtx ready to start a new one.Useful after an error, or to interrupt any ongoing compression.Any internal data not yet flushed is cancelled.Compression parameters and dictionary remain unchanged.They will be used to compress next frame.Resetting session never fails. 
	//-ZSTD_reset_parameters:              The parameters : changes all parameters back to "default".This removes any reference to any dictionary too.Parameters can only be changed between 2 sessions(i.e.no compression is currently ongoing) otherwise the reset fails, and function returns an error value(which can be tested using ZSTD_isError()) 
	//-ZSTD_reset_session_and_parameters:  Both : similar to resetting the session, followed by resetting parameters.

	//Есть 2 разных параметра, которые можно сбросить, независимо или совместно:
	//-ZSTD_reset_session_only:           Сессия: прекратит сжатие текущего кадра и подготовит CCtx к началу нового. Полезно после ошибки или для прерывания любого текущего сжатия. Любые внутренние данные, которые еще не были сброшены, отменяются. Параметры сжатия и словарь остаются неизменными. Они будут использоваться для сжатия следующего кадра. Сброс сеанса никогда не приводит к сбою.
	//-ZSTD_reset_parameters:             Параметры: изменяют все параметры обратно на «по умолчанию». Это также удаляет любые ссылки на любой словарь. Параметры можно изменять только между 2 сеансами (т. е. в данный момент сжатие не выполняется), в противном случае сброс не выполняется, и функция возвращает значение ошибки (которое можно проверить с помощью ZSTD_isError())
	//-ZSTD_reset_session_and_parameters: Оба: аналогично сбросу сеанса с последующим сбросом параметров.

	//Честно говоря хрен знает на что эти сбросы особо влияют, единсвенно что более менее понятно - это сброc "ZSTD_reset_parameters" - который сбрасывает все ранее дополнительно установленные параметры с помощью функции "set__param" - в состояние по умолчанию - ну так уровень сжатия, уровни скорости сжатия, окно буффера и прочие магические праметры.


	ZSTD_ResetDirective reset_param_4d = ZSTD_reset_parameters;

	result_4 = Zstd__Stream__Lambda__KnownFinalSize_.ResetContext_Uncompress(reset_param_4d);


	//------------------------------------------------------------------------------------------
	if (result_4 != Zstd__Stream__Lambda__KnownFinalSize::result_flag::OK)
	{
		std::cout << "error_4:" << Zstd__Stream__Lambda__KnownFinalSize_.get__ErrorName() << std::endl;

		return -1;
	}

	//------------------------------------------------------------------------------------


	//--------------------------------------------------------------------------------ResetContext_Uncompress:Конец--------------------------------------------------------------------------------------




	//************************************************************************************4-Zstd__Stream__KnownFinalSize:Конец************************************************************************************












	//************************************************************************************5-Zstd__Stream__Lambda__UnknownFinalSize:Начало************************************************************************************
	//Данная функция сжимает "потоковые данные" целевого "файла" по частям: размер всего итогового "файла" Не нужно знать и указывать заранее. Отличие от "Zstd__Stream__UnknownFinalSize" в дополнительном колбеке, который будет вызываться каждый раз для каждого сжимаемого-разжимаемого чанка.
	//Важно: Сжатие по частям, когда часть меньше размера самого буффера с данными - естесвенно менее эффективно по итогвому результату, если бы сжатие происходило бы всего буффера с входящими данными.
	//БОЛЕЕ ПОДРОБНО: предположим условно что с сети пришла часть файла, то есть просто массив данных известного размера, вызываем "run_StartStream" с флагом Stream_flag::continue_stream, теперь приходить вторая часть, НЕ Последняя из этого файла, вызываем "run_ContinueStream" с флагом Stream_flag::continue_stream, а теперь приходить тридцать вторая часть этого файла последняя, то есть эта часть завершающая часть этого файла, то для это части нужно вызвать Stream_flag::end_stream. 
	//ВОПРОС: однако я нифига не понимаю, в чем смысл использовать именно функцию потокового сжатия "ZSTD_compressStream2" для сжатия разных частей цельного файла, если можно использовать обычную функцию "ZSTD_compress" для пришедшей очередной части файла и результат просто добавлять в буффер результата, как это и делает функция  "Zstd__SimpleCompress/Zstd__SimpleCompress_CCtx" - единсвенно, что функция "Zstd__SimpleCompress/Zstd__SimpleCompress_CCtx" не подходит для разбития буффера на Чанки при сжатии, НО если разбивать на Чанки не нужно, тогда смысл специальной потоковй функции - не понятен мне.



	Zstd__Stream__Lambda__UnknownFinalSize Zstd__Stream__Lambda__UnknownFinalSize_;

	//Методы:
	//- run_StartStream
	//- run_ContinueStream
	//- set__StreamEnd
	//- run_Uncompress
	//- set__param_Сompress
	//- ResetContext_Uncompress
	//- set__param_Uncompress
	//- ResetContext_Сompress



	std::string balvanka_5_1 = "Hello1_Hello2_Hello3_Hello4_Hello5_Hello6_Hello7_Hello8_Hello9_Hello10!!!";
	std::string balvanka_5_2 = "Buy1_Buy2_Buy3_Buy4_Buy5_Buy6_Buy7_Buy8_Buy9_Buy10xxx";


	Zstd__Stream__Lambda__UnknownFinalSize::result_flag result_5;



	//--------------------------------------------------------------------------------------------run_StartStream, run_ContinueStream, set__StreamEnd:Начало---------------------------------------------------------------------------------------------------------

	//Функция сжимает данные в потоковом режиме с возможность сжатия предоставленного буффера данных по частям.


	//-------------------------------------------------------------------------------------------------
	const int numm_thread_5_1 = 0;                                               //Кол-во потоков процессора, который задействуется при сжатыи: 0 - Однопоточный режим.[Для задействования многопоточности должен быть опредлен define "ZSTD_MULTITHREAD"]

	const int level_compressed_5_1 = 21;                                         //Уровень сжатия: от 0 до 22. 0 - без сжатия ... 22 - масимальное сжатые.

	const size_t chunk_size_5_1 = 10;                                           //Размер в байтах части, которая будет считыватся из буффера с данными которые нужно сжать и эту считанную часть сжимать.Если делить на части буффер по указателю "char_p__to_data_should_be_compressed_7" и нужно сжать его, один куском, то просто указать размер буффера по этому указателю, то есть "size__data_to_be_compressed_7".

	const char* char_p__to_data_should_be_compressed_5_1 = &balvanka_5_1[0];     //Указатель на данные, которые нужно Сжать. Первая часть.

	size_t size__data_to_be_compressed_5_1 = balvanka_5_1.size();                //Размер данных, который должен быть Сжат.

	Zstd__Stream__Lambda__UnknownFinalSize::Stream_flag Stream_flag_5_1 = Zstd__Stream__Lambda__UnknownFinalSize::Stream_flag::continue_stream;     //Флаг состояния потока, читать Три читуации чуть ниже.
	//-------------------------------------------------------------------------------------------------


	//-------------------------------------------------------------------------------------------------
	std::string resultos_5c;
	std::function<void(const Zstd__Stream__Lambda__UnknownFinalSize::callback_flag status, const char* Pointer_to_ChunkBeforeCompressData, const size_t ChunkBeforeCompressData_size, const char* Pointer_to_ChunkCompressData, const size_t ChunkCompressData_size, const size_t approximate_MaxSize_for_CompressedResult, Zstd__Stream__Lambda__UnknownFinalSize* Zstd__Stream_p)> lambda_callback_5c = [&resultos_5c](const Zstd__Stream__Lambda__UnknownFinalSize::callback_flag status, const char* Pointer_to_ChunkBeforeCompressData, const size_t ChunkBeforeCompressData_size, const char* Pointer_to_ChunkCompressData, const size_t ChunkCompressData_size, const size_t garant_MaxSize_for_CompressedResult, Zstd__Stream__Lambda__UnknownFinalSize* Zstd__Stream_p)
		{


			//------------------------------------------------------------------------------------------------------
			if (status == Zstd__Stream__Lambda__UnknownFinalSize::callback_flag::data_chunk)
			{
				//ЗНАЧИТ что: данные на которые указывает:
				//"Pointer_to_ChunkBeforeCompressData" в кол-ве "ChunkBeforeCompressData_size"   - это очередная часть данных, из предсотавленного при вызове функции "run" указателя на буффер с данными которого нужно сжать. 
				//"ChunkBeforeCompressData_size"                                                 - это размер Чанка указанный ранее при вызове функции "run", НО может быть и меньше, если колбек вызвался для "хвоста".
				//"Pointer_to_ChunkCompressData"                                                 - указатель на сжатые данные размером "Pointer_to_ChunkCompressData", которые сжались из несжатых данных по указателю "Pointer_to_ChunkBeforeCompressData"
				//"Zstd__Stream_p"                                                  - указатель на класс, который вызвал данный колбек. Нафиг он нужен, да особо и не нужен, так просто на всякий случай.

				std::cout << Zstd__Stream_p->get__CallbackFlag_Name(status) << std::endl;

				std::string string_temp; string_temp.append(Pointer_to_ChunkCompressData, ChunkCompressData_size);  //Не факт, что "Pointer_to_ChunkCompressData" оканчивается нулем, поэтому скопируем ровно указанное кол-во, чтобы не выводить мусор.

				std::cout << "Pointer_to_ChunkCompressData:" << string_temp << std::endl;
			}

			if (status == Zstd__Stream__Lambda__UnknownFinalSize::callback_flag::ending_chunk)
			{
				//Значит это завершающий этап сжатия, функция еще выдает данные, но это уже не полезные данные сжатия, а какая то служеюная информация, которую естесвенно также нужно запиисывать в общией результативный буффер.

				std::cout << Zstd__Stream_p->get__CallbackFlag_Name(status) << std::endl;

				std::string string_temp; string_temp.append(Pointer_to_ChunkCompressData, ChunkCompressData_size);  //Не факт, что "Pointer_to_ChunkCompressData" оканчивается нулем, поэтому скопируем ровно указанное кол-во, чтобы не выводить мусор.

				std::cout << "Pointer_to_ChunkCompressData:" << string_temp << std::endl;
			}

			if (status == Zstd__Stream__Lambda__UnknownFinalSize::callback_flag::compression_completed)
			{
				//Это просто информионный кол-бек, который говорит, что все данные сжаты и сжатие завершено. Все указатели и размеры на данные - НЕ ДЕЙСТВИТЕЛЬНЫ.

				std::cout << Zstd__Stream_p->get__CallbackFlag_Name(status) << std::endl;
			}
			//------------------------------------------------------------------------------------------------------

			//------------------------------------------------------------------------------------------------------
			//approximate_MaxSize_for_CompressedResult - Это ПРИМЕРНЫЙ максимальный размер под все части данного вызова "run". ЕЩЕ РАЗ это ПРИМЕРНЫЙ "МАКСИМАЛЬНЫЙ" РАЗМЕР, размер может оказатся и больше и даже меньше. АКТУАЛЕН ТОЛЬКО ВО ВРЕМЯ ПЕРВОГО ВЫЗОВА ДАННОГО КОЛБЕКА, после очередного вызова метода "run" у класса.
			//------------------------------------------------------------------------------------------------------



			//---------------------------------------Добавляем данные в единый буффер:---------------------------------
			resultos_5c.append(Pointer_to_ChunkCompressData, ChunkCompressData_size);
			//-----------------------------------------------------------------------------

		};

	Zstd__Stream__Lambda__UnknownFinalSize_.set__LambdaCallback(lambda_callback_5c);  //Устанавливаем лямбду-колбек, который будет вызыватся каждый раз, как функция сожмет очередной Чанк. Установить требутся ДО первого вызовая "run" и только один раз. Если после установки нужно будет заменить дургим колбеком, меняем в любое необходимое время.
	//-------------------------------------------------------------------------------------------------




	//------------------------------------------------------------------------------------------
	//ВАЖНО, КАК ЗАПУСКАТЬ функии "run_xxx": примечаение: РАЗМЕР ВСЕГО ЦЕЛЬНОГО ФАЙЛА, ТО ЕСТЬ СУММА РАЗМЕРОВ ВСЕХ ЧАСТЕЙ ДОЛЖНА БЫТЬ ИЗВЕСТНА ЗАРАНЕЕ И УКАЗАНА ПРИ ПЕРВОМ ВЫЗОВЕ.
	//1-ситуация: предположим условно что с сети пришла часть файла, то есть просто массив данных известного размера и вызываем "run_StartStream" с флагом Stream_flag::continue_stream, теперь приходить вторая часть, НЕ Последняя из этого файла, вызываем "run_ContinueStream" также с флагом Stream_flag::continue_stream, а теперь приходить тридцать вторая часть этого файла последняя, то есть эта часть завершающая часть этого файла, то для вызывается "run_ContinueStream" с флагом Stream_flag::end_stream.
	//2-ситуация: предположим условно что с сети пришла часть файла, то есть просто массив данных известного размера и точно известно, что это первая и последняя часть целого файла, то вызываем "run_StartStream" с флагом Stream_flag::end_stream.
	//3-Ситуация: предположим условно что с сети пришла часть файла, то есть просто массив данных известного размера и на момент вызова "run_StartStream" с флагом Stream_flag::continue_stream - было не изветсно, что эта был последняя часть файла, а стал известно уже после вызова "run_StartStream", то потом просто нужно вызвать метод "set__StreamEnd()"


	result_5 = Zstd__Stream__Lambda__UnknownFinalSize_.run_StartStream(numm_thread_5_1, level_compressed_5_1, chunk_size_5_1, char_p__to_data_should_be_compressed_5_1, size__data_to_be_compressed_5_1, Stream_flag_5_1);

	//result_5 = Zstd__Stream__Lambda__UnknownFinalSize_.run_ContinueStream(chunk_size_5_1, char_p__to_data_should_be_compressed_5_1, size__data_to_be_compressed_5_1, Stream_flag_5_1);

	//result_5 = Zstd__Stream__Lambda__UnknownFinalSize_.set__StreamEnd();  //3-Ситуация


	if (result_5 != Zstd__Stream__Lambda__UnknownFinalSize::result_flag::OK)
	{
		std::cout << "Error_5:" << Zstd__Stream__Lambda__UnknownFinalSize_.get__ErrorName() << std::endl;

		return -1;
	}
	else
	{
		std::cout << "resultos_5c:" << resultos_5c << std::endl;
	}
	//------------------------------------------------------------------------------------------





	//------------------------------------------------------------------------------------------
	result_5 = Zstd__Stream__Lambda__UnknownFinalSize_.run_ContinueStream(20, &balvanka_5_2[0], balvanka_5_2.size(), Zstd__Stream__Lambda__UnknownFinalSize::Stream_flag::end_stream);   //Ставим флаг "конца потока", так как это последняя часть цельного файла.


	if (result_5 != Zstd__Stream__Lambda__UnknownFinalSize::result_flag::OK)
	{
		std::cout << "Error_5:" << Zstd__Stream__Lambda__UnknownFinalSize_.get__ErrorName() << std::endl;

		return -1;
	}
	else
	{
		std::cout << "resultos_5c:" << resultos_5c << std::endl;          //Выводим итоговые сжатые данные.
	}
	//------------------------------------------------------------------------------------------




	//--------------------------------------------------------------------------------------------run_StartStream, run_ContinueStream, set__StreamEnd:Конец---------------------------------------------------------------------------------------------------------





	//-------------------------------------------------------------------------------------------------------------run_Uncompress:Начало---------------------------------------------------------------------------------------------------------

	//Функция расжимает ранее сжатые пооковые данные.

	//--------------------------------------------------------------------------
	const size_t chunk_size_5_2 = 2;                                                                           //Размер Чанка в байтах, то есть функция будет расжимать данные по указателю "char_p__to_uncompressed_data_5_1" по частям. ЕСЛИ расжимать частями сжатые данные не нужно, то просто указать размер Чанка равному размеру самиx сжатых данных.

	const char* char_p__to_uncompressed_data_5_1 = &resultos_5c[0];                                             //Указатель на Сжатые данные, которые нужно разжать.

	const size_t size__uncompressed_data_5_1 = resultos_5c.size();                                              //Размер Сжатых данных, которые нужно разжать.


	std::string resultos_5d;
	std::function<void(const Zstd__Stream__Lambda__UnknownFinalSize::callback_flag status, const char* Pointer_to_ChunkBeforeUncompressData, const size_t ChunkBeforeUncompressData_size, const char* Pointer_to_ChunkUnompressData, const size_t ChunkUncompressData_size, Zstd__Stream__Lambda__UnknownFinalSize* Zstd__Stream__Lambda__UnknownFinalSize_p)> lambda_callback_5d = [&resultos_5d](const Zstd__Stream__Lambda__UnknownFinalSize::callback_flag status, const char* Pointer_to_ChunkBeforeUncompressData, const size_t ChunkBeforeUncompressData_size, const char* Pointer_to_ChunkUnompressData, const size_t ChunkUncompressData_size, Zstd__Stream__Lambda__UnknownFinalSize* Zstd__Stream__Lambda__UnknownFinalSize_p)
		{


			//------------------------------------------------------------------------------------------------------
			if (status == Zstd__Stream__Lambda__UnknownFinalSize::callback_flag::data_chunk)
			{
				//ЗНАЧИТ что: данные на которые указывает:
				//"Pointer_to_ChunkBeforeUncompressData" в кол-ве "ChunkBeforeCompressData_size" - это очередная часть данных, из предсотавленного при вызове функции "run" буффера - то есть данные которого нужно разжать. 
				//"ChunkBeforeUncompressData_size"                                               - это размер Чанка указанный ранее при вызове функции "run", НО может быть меньше, если колбек вызвался для "хвоста".
				//"Pointer_to_ChunkUnompressData"                                                - указатель на разжатые данные размером "ChunkUncompressData_size", которые разжались из сжатых данных по указателю "Pointer_to_ChunkBeforeUncompressData"
				//"Zstd__StreamUncompress_p"                                                - указатель на класс, который вызвал данный колбек. Нафиг он нужен, да особо и не нужен, так просто на всякий случай.

				std::cout << Zstd__Stream__Lambda__UnknownFinalSize_p->get__CallbackFlag_Name(status) << std::endl;

				std::string string_temp; string_temp.append(Pointer_to_ChunkUnompressData, ChunkUncompressData_size);  //Не факт, что "Pointer_to_ChunkUnompressData" оканчивается нулем, поэтому скопируем ровно указанное кол-во, чтобы не выводить мусор.

				std::cout << "Pointer_to_ChunkUnompressData:" << string_temp << std::endl;
			}

			if (status == Zstd__Stream__Lambda__UnknownFinalSize::callback_flag::decompression_completed)
			{
				//Это просто информионный кол-бек, который говорит, что все данные сжаты и сжатие завершено. Все указатели и размеры на данные - НЕ ДЕЙСТВИТЕЛЬНЫ.

				std::cout << Zstd__Stream__Lambda__UnknownFinalSize_p->get__CallbackFlag_Name(status) << std::endl;
			}
			//------------------------------------------------------------------------------------------------------


			//------------------------------------------------------------------------------------------------------
			//garant_MaxSize_for_CompressedResult - Это гарантированный максимальный размер, под ИТОГОВЫЕ сжатые данные - то есть если проссумировать все "ChunkCompressData_size" до последнего вызова данного колбека - сумма будет меньше или равна == garant_MaxSize_for_CompressedResult.
			//------------------------------------------------------------------------------------------------------



			//------------------------------Занесе данные:----------------------------------------------
			resultos_5d.append(Pointer_to_ChunkUnompressData, ChunkUncompressData_size);
			//-----------------------------------------------------------------------------------


		};
	//--------------------------------------------------------------------------



	//-------------------------------------------------------------------------------------------------------------------------
	//result_Uncumpress_5_1.resize(0);        //Так как функция добавляет Разжатые данные в конец переданного обьекта строки, то если там уже есть какие то данные, а записать нужно к примеру с начала, то перед вызвом функции нужно обнулить, если нужно чтобы в строке шли подряд два Фрейма сжатых данных, то менять размер соовтетвенно не нужно.

	result_5 = Zstd__Stream__Lambda__UnknownFinalSize_.run_Uncompress(chunk_size_5_2, char_p__to_uncompressed_data_5_1, size__uncompressed_data_5_1, lambda_callback_5d);


	if (result_5 != Zstd__Stream__Lambda__UnknownFinalSize::result_flag::OK)
	{
		std::cout << "Error_5:" << Zstd__Stream__Lambda__UnknownFinalSize_.get__ErrorName() << std::endl;

		return -1;
	}
	else
	{
		std::cout << "resultos_5d:" << resultos_5d << std::endl;             //Выводим рахжатые данные.
	}
	//-------------------------------------------------------------------------------------------------------------------------


	//-------------------------------------------------------------------------------------------------------------run_Uncompress:Начало---------------------------------------------------------------------------------------------------------










	//--------------------------------------------------------------------------set__param_Сompress:Начало---------------------------------------------------------------------------

	//Данная фукнция вызывает внутри "ZSTD_CCtx_setParameter" устанавливая дополнительно настраиваемые параметры сжатия.

		//---------------------------------------------------
		//Параметры и их описания, которые принимает функция ZSTD_CCtx_setParameter можно найти или в документации на странице: https://facebook.github.io/zstd/zstd_manual.html   - смотреть enum ZSTD_cParameter.
		//Или в исxодном файле zstd.h - смотреть тот же enum ZSTD_cParameter.

		//ZSTD_cParam_getBounds - данная функция принимает один из параметров "ZSTD_cParameter" и возвращает его минимальное и максимальное значение, которое предается в функцию "ZSTD_CCtx_setParameter" третьим "param_value" параметром.
		//ZSTD_bounds ZSTD_bounds_1 = ZSTD_cParam_getBounds(ZSTD_c_nbWorkers);
		//std::cout << "минимальные значение параметра:" << ZSTD_bounds_1.lowerBound << std::endl;
		//std::cout << "максимальное значение параметра:" << ZSTD_bounds_1.upperBound << std::endl;

		//Проверку на ошибку после вызова через  ZSTD_isError.
		//---------------------------------------------------



	//------------------------------------------------------------------------------------

	const ZSTD_cParameter param_5с = ZSTD_c_minMatch;  //Какой то один из параметров.
	const int param_value_5с = ZSTD_cParam_getBounds(param_5с).lowerBound;

	result_5 = Zstd__Stream__Lambda__UnknownFinalSize_.set__param_Compress(param_5с, param_value_5с);


	//------------------------------------------------------------------------------------------
	if (result_5 != Zstd__Stream__Lambda__UnknownFinalSize::result_flag::OK)
	{
		std::cout << "error_5:" << Zstd__Stream__Lambda__UnknownFinalSize_.get__ErrorName() << std::endl;

		return -1;
	}

	//------------------------------------------------------------------------------------


	//--------------------------------------------------------------------------set__param_Сompress:Начало---------------------------------------------------------------------------




	//--------------------------------------------------------------------------set__param_Uncompress:Начало---------------------------------------------------------------------------

	//Данная фукнция вызывает внутри "ZSTD_DCtx_setParameter" устанавливая дополнительно настраиваемые параметры дэкомпрессии.

		//---------------------------------------------------
		//Параметры и их описание, которые принимает функция ZSTD_DCtx_setParameter можно найти или в документации на странице: https://facebook.github.io/zstd/zstd_manual.html   - смотреть enum ZSTD_dParameter.
		//Или в исxодном файле zstd.h - смотреть тот же enum ZSTD_dParameter.


		//ZSTD_dParam_getBounds - данная функция принимает один из параметров "ZSTD_dParameter" и возвращает его минимальное и максимальное значение, которое предается в функцию "ZSTD_DCtx_setParameter" третьим "param_value" параметром.
		//ZSTD_bounds ZSTD_bounds_1 = ZSTD_dParam_getBounds(ZSTD_d_windowLogMax);
		//std::cout << "минимальные значение параметра:" << ZSTD_bounds_1.lowerBound << std::endl;
		//std::cout << "максимальное значение параметра:" << ZSTD_bounds_1.upperBound << std::endl;

		//Проверку на ошибку после вызова через ZSTD_isError.

		//---------------------------------------------------




	//------------------------------------------------------------------------------------
	const ZSTD_dParameter param_5d = ZSTD_d_windowLogMax;  //Какой то один из параметров.
	const int param_value_5d = ZSTD_dParam_getBounds(param_5d).lowerBound;

	result_5 = Zstd__Stream__Lambda__UnknownFinalSize_.set__param_Uncompress(param_5d, param_value_5d);


	//------------------------------------------------------------------------------------------
	if (result_5 != Zstd__Stream__Lambda__UnknownFinalSize::result_flag::OK)
	{
		std::cout << "error_5:" << Zstd__Stream__Lambda__UnknownFinalSize_.get__ErrorName() << std::endl;

		return -1;
	}

	//------------------------------------------------------------------------------------



	//--------------------------------------------------------------------------set__param_Uncompress:Конец---------------------------------------------------------------------------




	//--------------------------------------------------------------------------------ResetContext_Compress:Начало--------------------------------------------------------------------------------------

	//Вообщем данная функция внутри вызывает "ZSTD_CCtx_reset" то есь сбрасывает сосояние контекста дэкомпрессии. Как написано в документации: https://facebook.github.io/zstd/zstd_manual.html

	//Функция принимает тип "ZSTD_ResetDirective" смотреть в файле zstd.h:

	//typedef enum 
	//{
	//	ZSTD_reset_session_only = 1,
	//	ZSTD_reset_parameters = 2,
	//	ZSTD_reset_session_and_parameters = 3
	//} ZSTD_ResetDirective;


	//There are 2 different things that can be reset, independently or jointly : 
	//-ZSTD_reset_session_only:            The session : will stop compressing current frame, and make CCtx ready to start a new one.Useful after an error, or to interrupt any ongoing compression.Any internal data not yet flushed is cancelled.Compression parameters and dictionary remain unchanged.They will be used to compress next frame.Resetting session never fails. 
	//-ZSTD_reset_parameters:              The parameters : changes all parameters back to "default".This removes any reference to any dictionary too.Parameters can only be changed between 2 sessions(i.e.no compression is currently ongoing) otherwise the reset fails, and function returns an error value(which can be tested using ZSTD_isError()) 
	//-ZSTD_reset_session_and_parameters:  Both : similar to resetting the session, followed by resetting parameters.

	//Есть 2 разных параметра, которые можно сбросить, независимо или совместно:
	//-ZSTD_reset_session_only:           Сессия: прекратит сжатие текущего кадра и подготовит CCtx к началу нового. Полезно после ошибки или для прерывания любого текущего сжатия. Любые внутренние данные, которые еще не были сброшены, отменяются. Параметры сжатия и словарь остаются неизменными. Они будут использоваться для сжатия следующего кадра. Сброс сеанса никогда не приводит к сбою.
	//-ZSTD_reset_parameters:             Параметры: изменяют все параметры обратно на «по умолчанию». Это также удаляет любые ссылки на любой словарь. Параметры можно изменять только между 2 сеансами (т. е. в данный момент сжатие не выполняется), в противном случае сброс не выполняется, и функция возвращает значение ошибки (которое можно проверить с помощью ZSTD_isError())
	//-ZSTD_reset_session_and_parameters: Оба: аналогично сбросу сеанса с последующим сбросом параметров.

	//Честно говоря хрен знает на что эти сбросы особо влияют, единсвенно что более менее понятно - это сброc "ZSTD_reset_parameters" - который сбрасывает все ранее дополнительно установленные параметры с помощью функции "set__param" - в состояние по умолчанию - ну так уровень сжатия, уровни скорости сжатия, окно буффера и прочие магические праметры.


	ZSTD_ResetDirective reset_param_5c = ZSTD_reset_parameters;

	result_5 = Zstd__Stream__Lambda__UnknownFinalSize_.ResetContext_Compress(reset_param_5c);


	//------------------------------------------------------------------------------------------
	if (result_5 != Zstd__Stream__Lambda__UnknownFinalSize::result_flag::OK)
	{
		std::cout << "error_5:" << Zstd__Stream__Lambda__UnknownFinalSize_.get__ErrorName() << std::endl;

		return -1;
	}

	//------------------------------------------------------------------------------------


	//--------------------------------------------------------------------------------ResetContext_Compress:Конец--------------------------------------------------------------------------------------






	//--------------------------------------------------------------------------------ResetContext_Uncompress:Начало--------------------------------------------------------------------------------------

	//Вообщем данная функция внутри вызывает "ZSTD_DCtx_reset" то есь сбрасывает сосояние контекста дэкомпрессии. Как написано в документации: https://facebook.github.io/zstd/zstd_manual.html

	//Функция принимает тип "ZSTD_ResetDirective" смотреть в файле zstd.h:

	//typedef enum 
	//{
	//	ZSTD_reset_session_only = 1,
	//	ZSTD_reset_parameters = 2,
	//	ZSTD_reset_session_and_parameters = 3
	//} ZSTD_ResetDirective;


	//There are 2 different things that can be reset, independently or jointly : 
	//-ZSTD_reset_session_only:            The session : will stop compressing current frame, and make CCtx ready to start a new one.Useful after an error, or to interrupt any ongoing compression.Any internal data not yet flushed is cancelled.Compression parameters and dictionary remain unchanged.They will be used to compress next frame.Resetting session never fails. 
	//-ZSTD_reset_parameters:              The parameters : changes all parameters back to "default".This removes any reference to any dictionary too.Parameters can only be changed between 2 sessions(i.e.no compression is currently ongoing) otherwise the reset fails, and function returns an error value(which can be tested using ZSTD_isError()) 
	//-ZSTD_reset_session_and_parameters:  Both : similar to resetting the session, followed by resetting parameters.

	//Есть 2 разных параметра, которые можно сбросить, независимо или совместно:
	//-ZSTD_reset_session_only:           Сессия: прекратит сжатие текущего кадра и подготовит CCtx к началу нового. Полезно после ошибки или для прерывания любого текущего сжатия. Любые внутренние данные, которые еще не были сброшены, отменяются. Параметры сжатия и словарь остаются неизменными. Они будут использоваться для сжатия следующего кадра. Сброс сеанса никогда не приводит к сбою.
	//-ZSTD_reset_parameters:             Параметры: изменяют все параметры обратно на «по умолчанию». Это также удаляет любые ссылки на любой словарь. Параметры можно изменять только между 2 сеансами (т. е. в данный момент сжатие не выполняется), в противном случае сброс не выполняется, и функция возвращает значение ошибки (которое можно проверить с помощью ZSTD_isError())
	//-ZSTD_reset_session_and_parameters: Оба: аналогично сбросу сеанса с последующим сбросом параметров.

	//Честно говоря хрен знает на что эти сбросы особо влияют, единсвенно что более менее понятно - это сброc "ZSTD_reset_parameters" - который сбрасывает все ранее дополнительно установленные параметры с помощью функции "set__param" - в состояние по умолчанию - ну так уровень сжатия, уровни скорости сжатия, окно буффера и прочие магические праметры.


	ZSTD_ResetDirective reset_param_5d = ZSTD_reset_parameters;

	result_5 = Zstd__Stream__Lambda__UnknownFinalSize_.ResetContext_Uncompress(reset_param_5d);


	//------------------------------------------------------------------------------------------
	if (result_5 != Zstd__Stream__Lambda__UnknownFinalSize::result_flag::OK)
	{
		std::cout << "error_5:" << Zstd__Stream__Lambda__UnknownFinalSize_.get__ErrorName() << std::endl;

		return -1;
	}

	//------------------------------------------------------------------------------------


	//--------------------------------------------------------------------------------ResetContext_Uncompress:Конец--------------------------------------------------------------------------------------




	//************************************************************************************5-Zstd__Stream__Lambda__UnknownFinalSize:Конец************************************************************************************






    //****************************************************************************************6-Zstd__DictonaryCompression:Начало****************************************************************************************

	//Это класс сжатия и разжатия данных с использованием Словаря.


	Zstd__DictonaryCompression Zstd__DictonaryCompression_;


	//Методы:
	//- add__Dictonary
	//- set_Dict_Usage
	//- run_Compress
	//- set__param_Compress
	//- ResetContext_Compress
	//- set__param_Uncompress
	//- ResetContext_Uncompress



	std::string balvanka_6_1 = "Hello1_WOELD1_Hello2_WOELD2_Hello3_WOELD3_Hello4_WOELD4_Hello5_WOELD5_Hello6_WOELD6_Hello7_WOELD7_Hello8_WOELD8_Hello9_WOELD9_Hello10_WOELD10!!!";
	std::string balvanka_6_2 = "Buy1_GOODBUY1_Buy2_GOODBUY2_Buy3_GOODBUY3_Buy4_GOODBUY4_Buy5_GOODBUY5_Buy6_GOODBUY6_Buy7_GOODBUY7_Buy8_GOODBUY8_Buy9_GOODBUY9_Buy10_GOODBUY10xxx";



	Zstd__DictonaryCompression::result_flag result_6;


	//------------------------------------------------------------------------------add__Dictonary:Начало---------------------------------------------------------------------------
	//Данный метод добавляет примеры и создает словарь для Сжатия и последующего разжатия данных.


	const char* Name_dict_1 = "Name_1";              //Имя добавляемого словаря.

	const std::vector<std::string>vec_Dict_samples = { "Hello1", "Hello2", "Hello3", "Hello4", "Hello5" , "Hello6" , "Hello7" , "Hello8" , "Hello9" , "Hello6" };  //Вектор примеров для словоря.

	const int CompressedLevelDict = 0;              //Уровень сжатия словоря.


	result_6 = Zstd__DictonaryCompression_.add__Dictonary(Name_dict_1, vec_Dict_samples, CompressedLevelDict);           //Дбавляем словарь.

	if (result_6 != Zstd__DictonaryCompression::result_flag::OK)
	{
		std::cout << "error_6:" << Zstd__DictonaryCompression_.get__ErrorName();

		return -1;
	}


	result_6 = Zstd__DictonaryCompression_.add__Dictonary("Name_2", { "Buy", "GOODBUY2", "Buy1", "Buy2", "Buy3" , "Buy4" , "Buy5" , "Buy6" , "Buy7" , "you8" }, 0);           //Дбавляем словарь.

	if (result_6 != Zstd__DictonaryCompression::result_flag::OK)
	{
		std::cout << "error_6:" << Zstd__DictonaryCompression_.get__ErrorName();

		return -1;
	}

	//------------------------------------------------------------------------------add__Dictonary:Конец---------------------------------------------------------------------------




	//------------------------------------------------------------------------------set_Dict_Usage:Начало---------------------------------------------------------------------------
	//Данный метод устанавливает использование какого то из ранее добавоенных словарей для всех последующих операция Сжатия и Разжатия. 


	const char* Name_dict_use_1 = "Name_2";


	result_6 = Zstd__DictonaryCompression_.set_Dict_Usage(Name_dict_use_1);

	if (result_6 == Zstd__DictonaryCompression::result_flag::non_existent_dict_name)
	{
		std::cout << "error_6:" << Zstd__DictonaryCompression_.get__ErrorName();

		return -1;
	}

	//------------------------------------------------------------------------------set_Dict_Usage:Конец---------------------------------------------------------------------------






	//------------------------------------------------------------------------------run_Compress:Начало---------------------------------------------------------------------------
	//Данный метод сжимает данные используя ранее загруженный и установленный через метод "set_Dict_Usage" словарь.


	//--------------------------------------------------------
	const int Compressed_Level                             = 15;                           //Уровень сжатия словоря.

	const char*  char_p__to_data_should_be_compressed_6_1 = &balvanka_6_1[0];           //Указатель на данные, которые нужно сжать.
	
	const size_t size__data_to_be_compressed_6_1          = balvanka_6_1.size();        //Размер данных по указателю на данные, которые нужно сжать.

	std::string string_compressed_result_6_1;                                            //Сюда в случае успеха - функция добавит в конец сжатые данные в соотвествии с установленными парамтерами. В случае ошибки, память будет возвращена к тому значению, которое было до вызова функии.
	//--------------------------------------------------------



	//-----------------------------------------------------
	result_6 = Zstd__DictonaryCompression_.run_Compress(Compressed_Level, char_p__to_data_should_be_compressed_6_1, size__data_to_be_compressed_6_1, string_compressed_result_6_1);   //Сжимаем.
	
	if (result_6 != Zstd__DictonaryCompression::result_flag::OK)
	{
		std::cout << "error_6:" << Zstd__DictonaryCompression_.get__ErrorName();

		return -1;
	}
	else
	{
		std::cout << "string_compressed_result_6_1_SIZE:" << string_compressed_result_6_1.size() << std::endl;
		std::cout << "string_compressed_result_6_1:"      << string_compressed_result_6_1 << std::endl;
	}
	//-----------------------------------------------------



	//-----------------------------------------------------
	//string_compressed_result_6_1.resize(0);        //Так как функция добавляет Сжатые данные в конец переданного обьекта строки, то если там уже есть какие то данные, а записать нужно к примеру с начала, то перед вызвом функции нужно обнулить, если нужно чтобы в строке шли подряд два Фрейма сжатых данных, то менять размер соовтетвенно не нужно.
	
	//Если для сжатия этих данных нужно установить другой словарь, то вызываем метод "set_Dict_Usage" с сооветвующим именем ранее доабвленного словаря.

	result_6 = Zstd__DictonaryCompression_.run_Compress(21, &balvanka_6_2[0], balvanka_6_2.size(), string_compressed_result_6_1);   //Сжимаем.
	
	if (result_6 != Zstd__DictonaryCompression::result_flag::OK)
	{
		std::cout << "error_6:" << Zstd__DictonaryCompression_.get__ErrorName();

		return -1;
	}
	else
	{
		std::cout << "string_compressed_result_6_1_SIZE:" << string_compressed_result_6_1.size() << std::endl;
		std::cout << "string_compressed_result_6_1:"      << string_compressed_result_6_1 << std::endl;
	}
	//-----------------------------------------------------


	//------------------------------------------------------------------------------run_Compress:Начало---------------------------------------------------------------------------







	//-----------------------------------------------------------------------------run_Uncompress:Начало---------------------------------------------------------------------------
	//Данная функция расжимает ранее сжатые данные. Для Расжатия данных нужно установить с помошью метода "set_Dict_Usage" именно тот словарь, которым сжимались данные, указанные для Расжатия.


	//--------------------------------------------------------
	const char* char_p__to_compressed_data_6 = &string_compressed_result_6_1[0];               //Указатель на данные, которые ранее были сжаты и которые нужно разжать.

	const size_t size__compressed_data_6_1 = string_compressed_result_6_1.size();             //Размер данных по указателю на данные, которые ранее были сжаты и которые нужно разжать.

	std::string string_Uncompressed_result_6_1;                                                //Сюда в случае успеха - функция добавит в конец сжатые данные в соотвествии с установленными парамтерами. В случае ошибки, память будет возвращена к тому значению, которое было до вызова функии.
	//--------------------------------------------------------



	//-----------------------------------------------------
	//string_Uncompressed_result_6_1.resize(0);        //Так как функция добавляет Разжатые данные в конец переданного обьекта строки, то если там уже есть какие то данные, а записать нужно к примеру с начала, то перед вызвом функции нужно обнулить, если нужно чтобы в строке шли подряд два Фрейма сжатых данных, то менять размер соовтетвенно не нужно.

	
	result_6 = Zstd__DictonaryCompression_.run_Uncompress(string_Uncompressed_result_6_1, char_p__to_compressed_data_6, size__compressed_data_6_1);   //Расжимаем.

	if (result_6 != Zstd__DictonaryCompression::result_flag::OK)
	{
		std::cout << "error_6:" << Zstd__DictonaryCompression_.get__ErrorName();

		return -1;
	}
	else
	{
		std::cout << "string_Uncompressed_result_6_1_SIZE:" << string_Uncompressed_result_6_1.size() << std::endl;
		std::cout << "string_Uncompressed_result_6_1:"      << string_Uncompressed_result_6_1 << std::endl;
	}
	//-----------------------------------------------------



	//-----------------------------------------------------------------------------run_Uncompress:Конец---------------------------------------------------------------------------










	//--------------------------------------------------------------------------set__param_Сompress:Начало---------------------------------------------------------------------------

	//Данная фукнция вызывает внутри "ZSTD_CCtx_setParameter" устанавливая дополнительно настраиваемые параметры сжатия.

		//---------------------------------------------------
		//Параметры и их описания, которые принимает функция ZSTD_CCtx_setParameter можно найти или в документации на странице: https://facebook.github.io/zstd/zstd_manual.html   - смотреть enum ZSTD_cParameter.
		//Или в исxодном файле zstd.h - смотреть тот же enum ZSTD_cParameter.

		//ZSTD_cParam_getBounds - данная функция принимает один из параметров "ZSTD_cParameter" и возвращает его минимальное и максимальное значение, которое предается в функцию "ZSTD_CCtx_setParameter" третьим "param_value" параметром.
		//ZSTD_bounds ZSTD_bounds_1 = ZSTD_cParam_getBounds(ZSTD_c_nbWorkers);
		//std::cout << "минимальные значение параметра:" << ZSTD_bounds_1.lowerBound << std::endl;
		//std::cout << "максимальное значение параметра:" << ZSTD_bounds_1.upperBound << std::endl;

		//Проверку на ошибку после вызова через  ZSTD_isError.
		//---------------------------------------------------



	//------------------------------------------------------------------------------------
	
	const ZSTD_cParameter param_6с = ZSTD_c_minMatch;  //Какой то один из параметров.
	const int param_value_6с = ZSTD_cParam_getBounds(param_6с).lowerBound;

	result_6 = Zstd__DictonaryCompression_.set__param_Compress(param_6с, param_value_6с);


	//------------------------------------------------------------------------------------------
	if (result_6 != Zstd__DictonaryCompression::result_flag::OK)
	{
		std::cout << "error_6:" << Zstd__DictonaryCompression_.get__ErrorName() << std::endl;

		return -1;
	}
	
	//------------------------------------------------------------------------------------


	//--------------------------------------------------------------------------set__param_Сompress:Начало---------------------------------------------------------------------------




    //--------------------------------------------------------------------------set__param_Uncompress:Начало---------------------------------------------------------------------------
	
	//Данная фукнция вызывает внутри "ZSTD_DCtx_setParameter" устанавливая дополнительно настраиваемые параметры дэкомпрессии.

		//---------------------------------------------------
		//Параметры и их описание, которые принимает функция ZSTD_DCtx_setParameter можно найти или в документации на странице: https://facebook.github.io/zstd/zstd_manual.html   - смотреть enum ZSTD_dParameter.
		//Или в исxодном файле zstd.h - смотреть тот же enum ZSTD_dParameter.


		//ZSTD_dParam_getBounds - данная функция принимает один из параметров "ZSTD_dParameter" и возвращает его минимальное и максимальное значение, которое предается в функцию "ZSTD_DCtx_setParameter" третьим "param_value" параметром.
		//ZSTD_bounds ZSTD_bounds_1 = ZSTD_dParam_getBounds(ZSTD_d_windowLogMax);
		//std::cout << "минимальные значение параметра:" << ZSTD_bounds_1.lowerBound << std::endl;
		//std::cout << "максимальное значение параметра:" << ZSTD_bounds_1.upperBound << std::endl;

		//Проверку на ошибку после вызова через ZSTD_isError.

		//---------------------------------------------------




	//------------------------------------------------------------------------------------
	const ZSTD_dParameter param_6d = ZSTD_d_windowLogMax;  //Какой то один из параметров.
	const int param_value_6d = ZSTD_dParam_getBounds(param_6d).lowerBound;

	result_6 = Zstd__DictonaryCompression_.set__param_Uncompress(param_6d, param_value_6d);


	//------------------------------------------------------------------------------------------
	if (result_6 != Zstd__DictonaryCompression::result_flag::OK)
	{
		std::cout << "error_6:" << Zstd__DictonaryCompression_.get__ErrorName() << std::endl;

		return -1;
	}

	//------------------------------------------------------------------------------------



	//--------------------------------------------------------------------------set__param_Uncompress:Конец---------------------------------------------------------------------------




	//--------------------------------------------------------------------------------ResetContext_Compress:Начало--------------------------------------------------------------------------------------

	//Вообщем данная функция внутри вызывает "ZSTD_CCtx_reset" то есь сбрасывает сосояние контекста дэкомпрессии. Как написано в документации: https://facebook.github.io/zstd/zstd_manual.html

	//Функция принимает тип "ZSTD_ResetDirective" смотреть в файле zstd.h:

	//typedef enum 
	//{
	//	ZSTD_reset_session_only = 1,
	//	ZSTD_reset_parameters = 2,
	//	ZSTD_reset_session_and_parameters = 3
	//} ZSTD_ResetDirective;


	//There are 2 different things that can be reset, independently or jointly : 
	//-ZSTD_reset_session_only:            The session : will stop compressing current frame, and make CCtx ready to start a new one.Useful after an error, or to interrupt any ongoing compression.Any internal data not yet flushed is cancelled.Compression parameters and dictionary remain unchanged.They will be used to compress next frame.Resetting session never fails. 
	//-ZSTD_reset_parameters:              The parameters : changes all parameters back to "default".This removes any reference to any dictionary too.Parameters can only be changed between 2 sessions(i.e.no compression is currently ongoing) otherwise the reset fails, and function returns an error value(which can be tested using ZSTD_isError()) 
	//-ZSTD_reset_session_and_parameters:  Both : similar to resetting the session, followed by resetting parameters.

	//Есть 2 разных параметра, которые можно сбросить, независимо или совместно:
	//-ZSTD_reset_session_only:           Сессия: прекратит сжатие текущего кадра и подготовит CCtx к началу нового. Полезно после ошибки или для прерывания любого текущего сжатия. Любые внутренние данные, которые еще не были сброшены, отменяются. Параметры сжатия и словарь остаются неизменными. Они будут использоваться для сжатия следующего кадра. Сброс сеанса никогда не приводит к сбою.
	//-ZSTD_reset_parameters:             Параметры: изменяют все параметры обратно на «по умолчанию». Это также удаляет любые ссылки на любой словарь. Параметры можно изменять только между 2 сеансами (т. е. в данный момент сжатие не выполняется), в противном случае сброс не выполняется, и функция возвращает значение ошибки (которое можно проверить с помощью ZSTD_isError())
	//-ZSTD_reset_session_and_parameters: Оба: аналогично сбросу сеанса с последующим сбросом параметров.

	//Честно говоря хрен знает на что эти сбросы особо влияют, единсвенно что более менее понятно - это сброc "ZSTD_reset_parameters" - который сбрасывает все ранее дополнительно установленные параметры с помощью функции "set__param" - в состояние по умолчанию - ну так уровень сжатия, уровни скорости сжатия, окно буффера и прочие магические праметры.


	ZSTD_ResetDirective reset_param_6c = ZSTD_reset_parameters;

	result_6 = Zstd__DictonaryCompression_.ResetContext_Compress(reset_param_6c);


	//------------------------------------------------------------------------------------------
	if (result_6 != Zstd__DictonaryCompression::result_flag::OK)
	{
		std::cout << "error_6:" << Zstd__DictonaryCompression_.get__ErrorName() << std::endl;

		return -1;
	}

	//------------------------------------------------------------------------------------


	//--------------------------------------------------------------------------------ResetContext_Compress:Конец--------------------------------------------------------------------------------------






	//--------------------------------------------------------------------------------ResetContext_Uncompress:Начало--------------------------------------------------------------------------------------

	//Вообщем данная функция внутри вызывает "ZSTD_DCtx_reset" то есь сбрасывает сосояние контекста дэкомпрессии. Как написано в документации: https://facebook.github.io/zstd/zstd_manual.html

	//Функция принимает тип "ZSTD_ResetDirective" смотреть в файле zstd.h:

	//typedef enum 
	//{
	//	ZSTD_reset_session_only = 1,
	//	ZSTD_reset_parameters = 2,
	//	ZSTD_reset_session_and_parameters = 3
	//} ZSTD_ResetDirective;


	//There are 2 different things that can be reset, independently or jointly : 
	//-ZSTD_reset_session_only:            The session : will stop compressing current frame, and make CCtx ready to start a new one.Useful after an error, or to interrupt any ongoing compression.Any internal data not yet flushed is cancelled.Compression parameters and dictionary remain unchanged.They will be used to compress next frame.Resetting session never fails. 
	//-ZSTD_reset_parameters:              The parameters : changes all parameters back to "default".This removes any reference to any dictionary too.Parameters can only be changed between 2 sessions(i.e.no compression is currently ongoing) otherwise the reset fails, and function returns an error value(which can be tested using ZSTD_isError()) 
	//-ZSTD_reset_session_and_parameters:  Both : similar to resetting the session, followed by resetting parameters.

	//Есть 2 разных параметра, которые можно сбросить, независимо или совместно:
	//-ZSTD_reset_session_only:           Сессия: прекратит сжатие текущего кадра и подготовит CCtx к началу нового. Полезно после ошибки или для прерывания любого текущего сжатия. Любые внутренние данные, которые еще не были сброшены, отменяются. Параметры сжатия и словарь остаются неизменными. Они будут использоваться для сжатия следующего кадра. Сброс сеанса никогда не приводит к сбою.
	//-ZSTD_reset_parameters:             Параметры: изменяют все параметры обратно на «по умолчанию». Это также удаляет любые ссылки на любой словарь. Параметры можно изменять только между 2 сеансами (т. е. в данный момент сжатие не выполняется), в противном случае сброс не выполняется, и функция возвращает значение ошибки (которое можно проверить с помощью ZSTD_isError())
	//-ZSTD_reset_session_and_parameters: Оба: аналогично сбросу сеанса с последующим сбросом параметров.

	//Честно говоря хрен знает на что эти сбросы особо влияют, единсвенно что более менее понятно - это сброc "ZSTD_reset_parameters" - который сбрасывает все ранее дополнительно установленные параметры с помощью функции "set__param" - в состояние по умолчанию - ну так уровень сжатия, уровни скорости сжатия, окно буффера и прочие магические праметры.


	ZSTD_ResetDirective reset_param_6d = ZSTD_reset_parameters;

	result_6 = Zstd__DictonaryCompression_.ResetContext_Uncompress(reset_param_6d);


	//------------------------------------------------------------------------------------------
	if (result_6 != Zstd__DictonaryCompression::result_flag::OK)
	{
		std::cout << "error_6:" << Zstd__DictonaryCompression_.get__ErrorName() << std::endl;

		return -1;
	}

	//------------------------------------------------------------------------------------


	//--------------------------------------------------------------------------------ResetContext_Uncompress:Конец--------------------------------------------------------------------------------------



	//****************************************************************************************6-Zstd__DictonaryCompression:Конец****************************************************************************************



	


}

