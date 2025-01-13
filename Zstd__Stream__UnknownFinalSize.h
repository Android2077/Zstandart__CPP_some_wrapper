#pragma once

#include "Zstandard__settings.h"   


#include <iostream>
#include <string>   
#include <functional>   



class Zstd__Stream__UnknownFinalSize
{

public:


    Zstd__Stream__UnknownFinalSize()
    {
        Compress_struct_.ZSTD_CStream_ = ZSTD_createCStream();          //Создаем контекст потокого сжатия.

        Uncompress_struct_.ZSTD_DStream_ = ZSTD_createDStream();        //Создаем контекст потокого сжатия.
    }

    ~Zstd__Stream__UnknownFinalSize()
    {
        ZSTD_freeCStream(Compress_struct_.ZSTD_CStream_);               //Освобождаем контекст потокого сжатия.

        ZSTD_freeDStream(Uncompress_struct_.ZSTD_DStream_);             //Освобождаем контекст потокого сжатия.
    }



public:

    enum class result_flag : int
    {
        OK = 1,
        Zstadart_error = 2,
        bad_alloc = 3,
    };


    enum class callback_flag : int
    {
        data_chunk = 1,
        ending_chunk = 2,
        compression_completed = 3,
    };

    enum class Stream_flag : int
    {
        continue_stream = 1,
        end_stream = 2,
    };



public:

    const result_flag run_StartStream(const int num_thread, const int level_compressed, const size_t CHUNK_SIZE, const char* PointerToData_WhichShouldBe_Compressed, const size_t DataSize_WhichShouldBe_Compressed, std::string& string_CompressedResult, const Stream_flag User_Stream_flag)
    {


        //----------------------------------------------------------------------------------
        Compress_struct_.Stream_flag_ = User_Stream_flag;

        ZSTD_CCtx_reset(Compress_struct_.ZSTD_CStream_, ZSTD_reset_session_only);         //Я не уверен, что нужно сбрасывать сессионый параметр, каждый раз при завершении расжатия и по сути перед началом следующего расжатия, но пусть на всякий случай будет.
        //----------------------------------------------------------------------------------



        //--------------------------------------------------------------------
        const size_t size_BeforeResize = string_CompressedResult.size();
        //--------------------------------------------------------------------



        //**********************************************************************************0-Установим num_thread и level_compressed:Начало*********************************************************************************

        size_t status = ZSTD_CCtx_setParameter(Compress_struct_.ZSTD_CStream_, ZSTD_c_compressionLevel, level_compressed);     //Установим Пользовотельское значение уровня сжатия.

        status = ZSTD_CCtx_setParameter(Compress_struct_.ZSTD_CStream_, ZSTD_c_nbWorkers, num_thread);                               //Установим Пользовотельское значение кол-ва потоков.


        //-------------------------------------------------1-ZSTD_c_compressionLevel:начало-------------------------------------------
        unsigned int status_ = ZSTD_isError(status);

        if (status_ != 0)
        {
            ErrorName = "ZSTD_CCtx_setParameter: " + std::string(ZSTD_getErrorName(status));

            string_CompressedResult.resize(size_BeforeResize);     //Вовзратим размер, который передал Пользовтаель
            string_CompressedResult.shrink_to_fit();

            ZSTD_CCtx_reset(Compress_struct_.ZSTD_CStream_, ZSTD_reset_session_and_parameters);

            return result_flag::Zstadart_error;
        }
        //-------------------------------------------------1-ZSTD_c_compressionLevel:конец-------------------------------------------


        //**********************************************************************************0-Установим num_thread и level_compressed:Конец*********************************************************************************






        //**********************************************************************************1-Установим размер сжимаемых данных:Начало*********************************************************************************
        /*
        //Вообщем как я понял - функция "ZSTD_compressStream2", которая в данном случае используется для потокового сжатия - почему то не принимает на вход размер сжимаемых данных, поэтому установить заранее до вызова "ZSTD_compressStream2" этот размер можно спомощью "ZSTD_CCtx_setPledgedSrcSize" - хотя это вроде, как не обязательно, но если установить - то это более оптимизирует работу функции "ZSTD_compressStream2". Ну или как-то так.

        const size_t ZSTD_CCtx_setPledgedSrcSize_ = ZSTD_CCtx_setPledgedSrcSize(ZSTD_CStream_, DataSize_WhichShouldBe_Compressed);


        //-------------------------------------------------------------------------------------------------------------------
        unsigned int status_error = ZSTD_isError(ZSTD_CCtx_setPledgedSrcSize_);  //Проверяем последний вызов на наличие ошибки.

        if (status_error != 0)
        {
            ErrorName = "ZSTD_CCtx_setPledgedSrcSize: " + std::string(ZSTD_getErrorName(ZSTD_CCtx_setPledgedSrcSize_));

            string_CompressedResult.resize(size_BeforeResize);     //Вовзратим размер, который передал Пользовтаель
            string_CompressedResult.shrink_to_fit();

            ZSTD_CCtx_reset(ZSTD_CStream_, ZSTD_reset_session_and_parameters);

            return result_flag::Zstadart_error;
        }
        //--------------------------------------------------------------------------------------------------------------------
        */
        //**********************************************************************************1-Установим размер сжимаемых данных:Конец*********************************************************************************





       //------------------------------------------------------------------------------------------2-Запустим само сжатие:Начало-------------------------------------------------------------------------

        const result_flag result = Run_Compress(CHUNK_SIZE, size_BeforeResize, PointerToData_WhichShouldBe_Compressed, DataSize_WhichShouldBe_Compressed, string_CompressedResult);

        if (result != result_flag::OK)
        {
            ErrorName = "Run_Compress:" + ErrorName;

            string_CompressedResult.resize(size_BeforeResize);     //Вовзратим размер, который передал Пользовтаель
            string_CompressedResult.shrink_to_fit();

            ZSTD_CCtx_reset(Compress_struct_.ZSTD_CStream_, ZSTD_reset_session_and_parameters);

            return result;
        }

        //------------------------------------------------------------------------------------------2-Запустим само сжатие:Конец-------------------------------------------------------------------------



        return result_flag::OK;
    }

    const result_flag run_ContinueStream(const size_t CHUNK_SIZE, const char* PointerToData_WhichShouldBe_Compressed, const size_t DataSize_WhichShouldBe_Compressed, std::string& string_CompressedResult, const Stream_flag User_Stream_flag)
    {


        //----------------------------------------------------------------------------------
        Compress_struct_.Stream_flag_ = User_Stream_flag;
        //----------------------------------------------------------------------------------



        //--------------------------------------------------------------------
        const size_t size_BeforeResize = string_CompressedResult.size();
        //--------------------------------------------------------------------




        //**********************************************************************************1-Установим размер сжимаемых данных:Начало*********************************************************************************
        /*
        //Вообщем как я понял - функция "ZSTD_compressStream2", которая в данном случае используется для потокового сжатия - почему то не принимает на вход размер сжимаемых данных, поэтому установить заранее до вызова "ZSTD_compressStream2" этот размер можно спомощью "ZSTD_CCtx_setPledgedSrcSize" - хотя это вроде, как не обязательно, но если установить - то это более оптимизирует работу функции "ZSTD_compressStream2". Ну или как-то так.

        const size_t ZSTD_CCtx_setPledgedSrcSize_ = ZSTD_CCtx_setPledgedSrcSize(ZSTD_CStream_, DataSize_WhichShouldBe_Compressed);


        //-------------------------------------------------------------------------------------------------------------------
        unsigned int status_error = ZSTD_isError(ZSTD_CCtx_setPledgedSrcSize_);  //Проверяем последний вызов на наличие ошибки.

        if (status_error != 0)
        {
            ErrorName = "ZSTD_CCtx_setPledgedSrcSize: " + std::string(ZSTD_getErrorName(ZSTD_CCtx_setPledgedSrcSize_));

            string_CompressedResult.resize(size_BeforeResize);     //Вовзратим размер, который передал Пользовтаель
            string_CompressedResult.shrink_to_fit();

            ZSTD_CCtx_reset(ZSTD_CStream_, ZSTD_reset_session_and_parameters);

            return result_flag::Zstadart_error;
        }
        //--------------------------------------------------------------------------------------------------------------------
        */
        //**********************************************************************************1-Установим размер сжимаемых данных:Конец*********************************************************************************





       //------------------------------------------------------------------------------------------2-Запустим само сжатие:Начало-------------------------------------------------------------------------

        const result_flag result = Run_Compress(CHUNK_SIZE, size_BeforeResize, PointerToData_WhichShouldBe_Compressed, DataSize_WhichShouldBe_Compressed, string_CompressedResult);

        if (result != result_flag::OK)
        {
            ErrorName = "Run_Compress:" + ErrorName;

            string_CompressedResult.resize(size_BeforeResize);     //Вовзратим размер, который передал Пользовтаель
            string_CompressedResult.shrink_to_fit();

            ZSTD_CCtx_reset(Compress_struct_.ZSTD_CStream_, ZSTD_reset_session_and_parameters);

            return result;
        }

        //------------------------------------------------------------------------------------------2-Запустим само сжатие:Конец-------------------------------------------------------------------------



        return result_flag::OK;
    }

    const result_flag set__StreamEnd(std::string& string_CompressedResult)
    {
        return Run_Compress_EndDirective_Handler(string_CompressedResult);
    }

    inline const result_flag set__param_Compress(const ZSTD_cParameter param, const int param_value)
    {

        size_t result = ZSTD_CCtx_setParameter(Compress_struct_.ZSTD_CStream_, param, param_value);


        //---------------------------------------------------
        //Параметры и их описание, которые принимает функция ZSTD_CCtx_setParameter можно найти или в документации на странице: https://facebook.github.io/zstd/zstd_manual.html   - смотреть enum ZSTD_cParameter.
        //Или в исxодном файле zstd.h - смотреть тот же enum ZSTD_cParameter.

        /*
        ZSTD_cParam_getBounds - данная функция принимает один из параметров "ZSTD_cParameter" и возвращает его минимальное и максимальное значение, которое предается в функцию "ZSTD_CCtx_setParameter" третьим "param_value" параметром.
        ZSTD_bounds ZSTD_bounds_1 = ZSTD_cParam_getBounds(ZSTD_c_nbWorkers);
        std::cout << "минимальные значение параметра:" << ZSTD_bounds_1.lowerBound << std::endl;
        std::cout << "максимальное значение параметра:" << ZSTD_bounds_1.upperBound << std::endl;

        Проверку на ошибку после вызова через  ZSTD_isError.
        */
        //---------------------------------------------------


        //-------------------------------------------------1-ZSTD_c_compressionLevel:начало-------------------------------------------
        unsigned int status_error = ZSTD_isError(result);

        if (status_error != 0)
        {
            ErrorName = "ZSTD_CCtx_setParameter: " + std::string(ZSTD_getErrorName(result));

            ZSTD_CCtx_reset(Compress_struct_.ZSTD_CStream_, ZSTD_reset_session_and_parameters);

            return result_flag::Zstadart_error;
        }
        //-------------------------------------------------1-ZSTD_c_compressionLevel:конец-------------------------------------------


        return result_flag::OK;

    }

    inline const result_flag ResetContext_Compress(const ZSTD_ResetDirective reset_flag)
    {

        size_t result = ZSTD_CCtx_reset(Compress_struct_.ZSTD_CStream_, reset_flag);


        //-------------------------------------------------------------
        unsigned int status_error = ZSTD_isError(result);

        if (status_error != 0)
        {
            ErrorName = "ZSTD_CCtx_reset: " + std::string(ZSTD_getErrorName(result));

            return result_flag::Zstadart_error;
        }
        //-------------------------------------------------------------


        return result_flag::OK;
    }




    const result_flag run_Uncompress(const size_t CHUNK_SIZE, const char* PointerToData_WhichShouldBe_Uncompressed, const size_t DataSize_WhichShouldBe_Uncompressed, std::string& string_UnUncompressedResult)
    {



        //----------------------------------------------------------------------------------
        ZSTD_DCtx_reset(Uncompress_struct_.ZSTD_DStream_, ZSTD_reset_session_only);         //Я не уверен, что нужно сбрасывать сессионый параметр, каждый раз при новом расжатия, но пусть на всякий случай будет.
        //----------------------------------------------------------------------------------



        //--------------------------------------------------------------------
        const size_t size_BeforeResize = string_UnUncompressedResult.size();
        //--------------------------------------------------------------------




       //------------------------------------------------------------------------------------------2-Запустим само сжатие:Начало-------------------------------------------------------------------------

        const result_flag result = Run_Uncompress_(CHUNK_SIZE, size_BeforeResize, PointerToData_WhichShouldBe_Uncompressed, DataSize_WhichShouldBe_Uncompressed, string_UnUncompressedResult);

        if (result != result_flag::OK)
        {
            ErrorName = "Run_Uncompress_:" + ErrorName;

            ZSTD_DCtx_reset(Uncompress_struct_.ZSTD_DStream_, ZSTD_reset_session_and_parameters);

            return result;
        }

        //------------------------------------------------------------------------------------------2-Запустим само сжатие:Конец-------------------------------------------------------------------------



        return result_flag::OK;
    }

    inline const result_flag set__param_Uncompress(const ZSTD_dParameter param, const int param_value)
    {

        size_t result = ZSTD_DCtx_setParameter(Uncompress_struct_.ZSTD_DStream_, param, param_value);


        //---------------------------------------------------
        //Параметры и их описание, которые принимает функция ZSTD_CCtx_setParameter можно найти или в документации на странице: https://facebook.github.io/zstd/zstd_manual.html   - смотреть enum ZSTD_cParameter.
        //Или в исxодном файле zstd.h - смотреть тот же enum ZSTD_cParameter.

        /*
        ZSTD_cParam_getBounds - данная функция принимает один из параметров "ZSTD_cParameter" и возвращает его минимальное и максимальное значение, которое предается в функцию "ZSTD_CCtx_setParameter" третьим "param_value" параметром.
        ZSTD_bounds ZSTD_bounds_1 = ZSTD_cParam_getBounds(ZSTD_c_nbWorkers);
        std::cout << "минимальные значение параметра:" << ZSTD_bounds_1.lowerBound << std::endl;
        std::cout << "максимальное значение параметра:" << ZSTD_bounds_1.upperBound << std::endl;

        Проверку на ошибку после вызова через  ZSTD_isError.
        */
        //---------------------------------------------------


        //-------------------------------------------------1-ZSTD_c_compressionLevel:начало-------------------------------------------
        unsigned int status_error = ZSTD_isError(result);

        if (status_error != 0)
        {
            ErrorName = "ZSTD_DCtx_setParameter: " + std::string(ZSTD_getErrorName(result));

            ZSTD_DCtx_reset(Uncompress_struct_.ZSTD_DStream_, ZSTD_reset_session_and_parameters);

            return result_flag::Zstadart_error;
        }
        //-------------------------------------------------1-ZSTD_c_compressionLevel:конец-------------------------------------------


        return result_flag::OK;

    }

    inline const result_flag ResetContext_Uncompress(const ZSTD_ResetDirective reset_flag)
    {

        size_t result = ZSTD_DCtx_reset(Uncompress_struct_.ZSTD_DStream_, reset_flag);


        //-------------------------------------------------------------
        unsigned int status_error = ZSTD_isError(result);

        if (status_error != 0)
        {
            ErrorName = "ZSTD_DCtx_reset: " + std::string(ZSTD_getErrorName(result));

            return result_flag::Zstadart_error;
        }
        //-------------------------------------------------------------


        return result_flag::OK;
    }




    const std::string& get__ErrorName() const
    {
        return ErrorName;
    }

    const std::string get__CallbackFlag_Name(const callback_flag callback_flag_)
    {

        if (callback_flag_ == callback_flag::data_chunk)
        {
            return "data_chunk";
        }
        else if (callback_flag_ == callback_flag::ending_chunk)
        {
            return "ending_chunk";
        }
        else if (callback_flag_ == callback_flag::compression_completed)
        {
            return "compression_completed";
        }

    }


private:


    struct Compress_struct
    {

        //-----------------------------------
        ZSTD_CStream* ZSTD_CStream_;

        ZSTD_outBuffer output;                 //Вообщем это структура для указания функции ZSTD_compressStream2, куда и какого размер функции помешать сжатую порцию данных.
        size_t total_WritingBytes;

        ZSTD_inBuffer input;
        //-----------------------------------
        Stream_flag Stream_flag_;
        //-----------------------------------
        size_t CHUNK_SIZE_this = 0;
        size_t CHUNK_TailSize_this = 0;
        //-----------------------------------

    }Compress_struct_;





    struct Uncompress_struct
    {

        //-----------------------------------
        ZSTD_DStream* ZSTD_DStream_;

        ZSTD_outBuffer output;                 //Вообщем это структура для указания функции ZSTD_decompressStream, куда и какого размера размер функции помещать расжатую информацию.

        ZSTD_inBuffer input;
        //-----------------------------------
        size_t CHUNK_SIZE_this = 0;
        size_t CHUNK_TailSize_this = 0;
        //-----------------------------------

    }Uncompress_struct_;


    std::string ErrorName;


    //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    const result_flag Run_Compress(const size_t CHUNK_SIZE, const size_t size_BeforeResize, const char* PointerToData_WhichShouldBe_Compressed, const size_t DataSize_WhichShouldBe_Compressed, std::string& string_CompressedResult)
    {



        //----------------------------------------------------------------Расчитаем целое кол-во Чанков и хвост:Начало-----------------------------------------------------------------

        //Короче, предположим пользовтаель указал указатель на данные, которые нужно сжать и указал их размер в 123 байта, и размер Чанка в 10 байт.
        //Итого получается, что у нас есть 123/10 = 12 целых проходов по 10 байт и 3 байтовый хвост, который неполучится оброботать 10 байтовым Чанком, а значит этот хвост прижется обработать отдельно от основного цикла.

        //ИЛИ ЖЕ можно просто ту по в цикле каждую итерацию проверять, сколько байт осталось обработать и сравнивать их с 10 байтовых Чанком, но, как по мне это просто бессмысленное трата на сравнение - ради одного единсвенного хвоста.

        //----------------------------------------------------------------------------------
        size_t Loop_number;

        if (CHUNK_SIZE > DataSize_WhichShouldBe_Compressed)
        {
            //Значит указанный CHUNK_SIZE больше, чем размер самого буффера "PointerToData_WhichShouldBe_Compressed".

            Compress_struct_.CHUNK_SIZE_this = DataSize_WhichShouldBe_Compressed;       //Значит ставим Размер чанка равным размеру буффера данных которые нужно сжать.
            Compress_struct_.CHUNK_TailSize_this = 0;                                       //Хвоста значит нет.
            Loop_number = 1;
        }
        else
        {
            Loop_number = DataSize_WhichShouldBe_Compressed / CHUNK_SIZE;  //В типе size_t любая дробная часть автоматчиески отбросится, поэтому получим чистое целое.

            Compress_struct_.CHUNK_SIZE_this = CHUNK_SIZE;
            Compress_struct_.CHUNK_TailSize_this = DataSize_WhichShouldBe_Compressed - Loop_number * CHUNK_SIZE;  //Расчитаем размер хвоста.
            Loop_number = DataSize_WhichShouldBe_Compressed / CHUNK_SIZE;                        //В типе size_t любая дробная часть автоматчиески отбросится, поэтому получим чистое целое.
        }
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------Расчитаем целое кол-во Чанков и хвост:Конец-----------------------------------------------------------------




        //-----------------------------------------------------------Расчитаем максимальный Гарантированный размер под итоговые сжатые данные:Начало--------------------------------------------------------------

        //const size_t garant_MaxSize_for_CompressedResult = ZSTD_compressBound(DataSize_WhichShouldBe_Compressed);   //Вообщем функция принимает исходный размер данных, который нужно сжать и возвращает теоретически Максимальный размер после сжатия, но размер после сжатия может быть в итоге и меньше. НО!!! данная функция не учитывает завершающие заголовки при потоковом сжатии при использовании директивы ZSTD_e_end, поэтому к резульату функции прибавим "GarantSize_for_EndHeader" = 100 байт, чтобы гарантировать, что завершающий заголовок поместится в выделенный буффер.
        //Походу нихрена это не макимальный гарантированный размер, так как "ZSTD_compressBound" как то нерпавильно расчитывает по крайней мере в связке с потоковой функией сжатия "ZSTD_compressStream2".
       
        //ПОЭТОМУ возьмем просто примерный такой размер для резервирования: 
        const size_t garant_MaxSize_for_CompressedResult = Compress_struct_.CHUNK_SIZE_this + DataSize_WhichShouldBe_Compressed / 3;
        //-----------------------------------------------------------Расчитаем максимальный Гарантированный размер под итоговые сжатые данные:Начало--------------------------------------------------------------

        //------------------------------------------------------
        try { string_CompressedResult.resize(size_BeforeResize + garant_MaxSize_for_CompressedResult); } catch (const std::bad_alloc& e) { ErrorName = e.what(); return  result_flag::bad_alloc; }  //Выделяем память под выходной буффер, в который будет записыватся частичный результат сжатия.
        //------------------------------------------------------






        //------------------------------------------------------------------------------------------------------------------------
        //ZSTD_EndDirective ZSTD_EndDirective_ = ZSTD_e_continue;        //Указание для функции ZSTD_compressStream2, что делать при вызове.
        //------------------------------------------------------------------------------------------------------------------------
        /*
        typedef enum
        {
            ZSTD_e_continue = 0, // собирайте больше данных, кодировщик решает, когда выводить сжатый результат, для оптимального коэффициента сжатия
            ZSTD_e_flush = 1, // очищайте все предоставленные данные,                                                                                   //ИСПОЛЬЗУЕМ ЭТО, чтобы функция ZSTD_compressStream2 брала часть из Входящего буффера данных которые нужно сжать в размере "CHUNK_SIZE" и сразу же их сжимала Не накапливая вхоядщие данные для более эффективноего сжатия, как при флаге "ZSTD_e_continue"
            - это создает (как минимум) один новый блок, который можно декодировать сразу после получения;
            - кадр будет продолжен: любые будущие данные могут ссылаться на ранее сжатые данные, улучшая сжатие.
            - примечание: многопоточное сжатие будет блокироваться до тех пор, пока не будет выведено как можно больше данных.
            ZSTD_e_end = 2 // выведите все оставшиеся данные и закройте текущий кадр.  примечание: кадр закрывается только после полной выгрузки сжатых данных (возвращаемое значение == 0).
            - После этого любые дополнительные данные начинают новый кадр.
            - примечание: каждый кадр является независимым (не ссылается на содержимое предыдущего кадра).
            : примечание: многопоточное сжатие будет блокироваться для очистки как можно большего объема вывода.
        } ZSTD_EndDirective;
        */
        //------------------------------------------------------------------------------------------------------------------------


        //-------------------------------------------------------------------------------------------------------------
        /*
        typedef struct ZSTD_outBuffer_s
        {
        void* dst;         // start of output buffer
        size_t size;       // < size of output buffer
        size_t pos;        // < position where writing stopped. Will be updated. Necessarily 0 <= pos <= size
        } ZSTD_outBuffer;
        //-------------------------------------------------------------------------------------------------------------
        typedef struct ZSTD_inBuffer_s
        {
            const void* src;    // start of input buffer
            size_t size;        //  size of input buffer
            size_t pos;         // position where reading stopped. Will be updated. Necessarily 0 <= pos <= size
        } ZSTD_inBuffer;
        */
        //-------------------------------------------------------------------------------------------------------------



        //-----------------------------------
        size_t total_ReadingBytes = 0;                       //Суммарно кол-во прочитанных байт, которые нужно сжать, то есть кол-во байт, которые нужно сжать - то есть число, которое уже было обработано и сжато.
        Compress_struct_.total_WritingBytes        = size_BeforeResize;       //Суммарно кол-во Сжатых байт в моменте. Нужно для определения смещения в "string_CompressedResult"
        //-----------------------------------



        //-------------------------------------------------------------------------------------------
        result_flag result_;

        result_ = Run_Compress_MainLoop(Loop_number, total_ReadingBytes, Compress_struct_.CHUNK_SIZE_this, PointerToData_WhichShouldBe_Compressed, string_CompressedResult); if (result_ != result_flag::OK) { string_CompressedResult.resize(size_BeforeResize); return result_; }

        //-------------------------------------------------------Обработаем хвост:Начало-------------------------------------------
        if (Compress_struct_.CHUNK_TailSize_this != 0)
        {
            result_ = Run_Compress_Tail_Handler(total_ReadingBytes, Compress_struct_.CHUNK_TailSize_this, PointerToData_WhichShouldBe_Compressed, string_CompressedResult);   if (result_ != result_flag::OK) { string_CompressedResult.resize(size_BeforeResize); return result_; }
        }
        //-------------------------------------------------------Обработаем хвост:Конец-------------------------------------------
        if (Compress_struct_.Stream_flag_ == Stream_flag::end_stream)
        {
            result_ = Run_Compress_EndDirective_Handler(string_CompressedResult);
        }
        //-------------------------------------------------------------------------------------------



        //------------------------------------------------------------
        string_CompressedResult.resize(Compress_struct_.total_WritingBytes);        //Корректируем размер под актульные данные.
        string_CompressedResult.shrink_to_fit();
        //------------------------------------------------------------



        return result_;
    }


    inline const result_flag Run_Compress_MainLoop(const size_t Loop_number, size_t& total_ReadingBytes, const size_t CHUNK_SIZE, const char* PointerToData_WhichShouldBe_Compressed, std::string& string_CompressedResult)
    {

         
        Compress_struct_.output = { &string_CompressedResult[Compress_struct_.total_WritingBytes], CHUNK_SIZE, 0 };   //Записываем в структуру ZSTD_outBuffer - данные: указатель на буффер куда нужно помещать сжатые данные, размер этого буффера и позиция в буффере, в данном случае позизиция всегда нулевая. ВАЖНО!!!: После вызова "ZSTD_compressStream2" она внутри у себя обновит третье поле .pos - куда запишет кол-во сжатых байт и записанных по указанному указателю.



        //***************************************************************************************************************************************************************************

        for (size_t i = 0; i < Loop_number; i++)
        {


            //-------------------------------------------------------------------------------------
            Compress_struct_.input = { PointerToData_WhichShouldBe_Compressed + total_ReadingBytes, CHUNK_SIZE, 0 };      //Указываем указатель на буффер с данными, который нужно сжать и размер данных, которые нужно сжать. Третий параметр функция "ZSTD_compressStream2" обновляет у себя внутри указывая на кол-по прочитанных байт по указаннмоу указателю в кол-ве "CHUNK_SIZE" байт. ТО ЕСТЬ, функцию "ZSTD_compressStream2" нужно вызывать в цикле до тех пор, пока третий параметр по значению не станет равным == CHUNK_SIZE - что будет означать, что данная порция данных прочитана и сжата. ПОСЛЕ ЧЕГО если есть еще одна порция данных для сжатия - то смещаем или меняем указатель на новые данные которые нужно сжать, устанавливаем нужный размер и ТРЕТИЙ ПАРАМТР ОПЯТЬ ЗАНУЛЯЕТСЯ, чтобы функция начала читать с первого байта по указанном указателю.
            //-------------------------------------------------------------------------------------



            //***************************************************************************************************************************************************************
            while (Compress_struct_.input.pos < CHUNK_SIZE)
            {

                //-------------------------------------------------ZSTD_compressStream2:Начало------------------------------------------------------------------

                const size_t ZSTD_compressStream2_FinalySize = ZSTD_compressStream2(Compress_struct_.ZSTD_CStream_, &(Compress_struct_.output), &(Compress_struct_.input), ZSTD_e_flush);               //Собстно вызываем функцию сжатия.


                //```````````````````````````````````````````````````````````````````````
                unsigned int status_error = ZSTD_isError(ZSTD_compressStream2_FinalySize);  //Проверяем последний вызов на наличие ошибки.

                if (status_error != 0)
                {
                    ErrorName = "ZSTD_compressStream2: " + std::string(ZSTD_getErrorName(ZSTD_compressStream2_FinalySize));

                    ZSTD_CCtx_reset(Compress_struct_.ZSTD_CStream_, ZSTD_reset_session_and_parameters);

                    return result_flag::Zstadart_error;
                }
                //```````````````````````````````````````````````````````````````````````

                //output.pos - теперь тут обвновленные данные, которые функция "ZSTD_compressStream2" занесла в это поле, которое говорит о том, сколько байт было записано по указателю "output.dst".
                //input.pos  - теперь тут обвновленные данные, которые функция "ZSTD_compressStream2" занесла в это поле, которое говорит о том, скольок байт было прочитано из указателя на данные которые нужно сжать.

                //-------------------------------------------------ZSTD_compressStream2:Конец------------------------------------------------------------------



                //----------------------------------------------Вызываем Пользовательский колбек:Начало--------------------------------
                if (Compress_struct_.output.pos != 0)
                {
                    //Значит ZSTD_compressStream2 - записала часть каких то сжатых данных, отправим их Пользователю:

                    Compress_struct_.total_WritingBytes = Compress_struct_.total_WritingBytes + Compress_struct_.output.pos;

                    check_ResizeBuff(string_CompressedResult, Compress_struct_.total_WritingBytes, CHUNK_SIZE);     //Проверяем нужно ли расширить размер "string_CompressedResult" с учетом индекса "total_WritingBytes".

                    Compress_struct_.output = { &string_CompressedResult[Compress_struct_.total_WritingBytes], CHUNK_SIZE, 0 };   //Записываем в структуру ZSTD_outBuffer - данные: указатель на буффер куда нужно помещать сжатые данные, размер этого буффера и позиция в буффере, в данном случае позизиция всегда нулевая. ВАЖНО!!!: После вызова "ZSTD_compressStream2" она внутри у себя обновит третье поле .pos - куда запишет кол-во сжатых байт и записанных по указанному указателю.
                }
                //----------------------------------------------Вызываем Пользовательский колбек:Начало--------------------------------

            }
            //***************************************************************************************************************************************************************


            total_ReadingBytes = total_ReadingBytes + CHUNK_SIZE;   //Суммируем обработанную порцию данных, которые нужно сжать, чтобы потом сместить его на это значение, для дальнейшей порции обработки данных.

        }

        //***************************************************************************************************************************************************************************



        return result_flag::OK;
    }
    inline const result_flag Run_Compress_Tail_Handler(const size_t total_ReadingBytes, const size_t CHUNK_TailSize, const char* PointerToData_WhichShouldBe_Compressed, std::string& string_CompressedResult)
    {


        //-------------------------------------------------------------------------------------
        Compress_struct_.input = { PointerToData_WhichShouldBe_Compressed + total_ReadingBytes, CHUNK_TailSize, 0 };      //Указываем указатель на буффер с данными, который нужно сжать и размер данных, которые нужно сжать. Третий параметр функция "ZSTD_compressStream2" обновляет у себя внутри указывая на кол-по прочитанных байт по указаннмоу указателю в кол-ве "CHUNK_SIZE" байт. ТО ЕСТЬ, функцию "ZSTD_compressStream2" нужно вызывать в цикле до тех пор, пока третий параметр по значению не станет равным == CHUNK_SIZE - что будет означать, что данная порция данных прочитана и сжата. ПОСЛЕ ЧЕГО если есть еще одна порция данных для сжатия - то смещаем или меняем указатель на новые данные которые нужно сжать, устанавливаем нужный размер и ТРЕТИЙ ПАРАМТР ОПЯТЬ ЗАНУЛЯЕТСЯ, чтобы функция начала читать с первого байта по указанном указателю.
        //-------------------------------------------------------------------------------------


        Compress_struct_.output = { &string_CompressedResult[Compress_struct_.total_WritingBytes], CHUNK_TailSize, 0 };   //Записываем в структуру ZSTD_outBuffer - данные: указатель на буффер куда нужно помещать сжатые данные, размер этого буффера и позиция в буффере, в данном случае позизиция всегда нулевая. ВАЖНО!!!: После вызова "ZSTD_compressStream2" она внутри у себя обновит третье поле .pos - куда запишет кол-во сжатых байт и записанных по указанному указателю.



        //***************************************************************************************************************************************************************
        while (Compress_struct_.input.pos < CHUNK_TailSize)
        {

        
            //-------------------------------------------------ZSTD_compressStream2:Начало------------------------------------------------------------------

            const size_t ZSTD_compressStream2_FinalySize = ZSTD_compressStream2(Compress_struct_.ZSTD_CStream_, &(Compress_struct_.output), &(Compress_struct_.input), ZSTD_e_continue);               //Собстно вызываем функцию сжатия.


            //```````````````````````````````````````````````````````````````````````
            unsigned int status_error = ZSTD_isError(ZSTD_compressStream2_FinalySize);  //Проверяем последний вызов на наличие ошибки.

            if (status_error != 0)
            {
                ErrorName = "ZSTD_compressStream2: " + std::string(ZSTD_getErrorName(ZSTD_compressStream2_FinalySize));

                ZSTD_CCtx_reset(Compress_struct_.ZSTD_CStream_, ZSTD_reset_session_and_parameters);

                return result_flag::Zstadart_error;
            }
            //```````````````````````````````````````````````````````````````````````

            //output.pos - теперь тут обвновленные данные, которые функция "ZSTD_compressStream2" занесла в это поле, которое говорит о том, сколько байт было записано по указателю "output.dst".
            //input.pos  - теперь тут обвновленные данные, которые функция "ZSTD_compressStream2" занесла в это поле, которое говорит о том, скольок байт было прочитано из указателя на данные которые нужно сжать.

            //-------------------------------------------------ZSTD_compressStream2:Конец------------------------------------------------------------------



            //----------------------------------------------Вызываем Пользовательский колбек:Начало--------------------------------
            if (Compress_struct_.output.pos != 0)
            {
                //Значит ZSTD_compressStream2 - записала часть каких то сжатых данных, отправим их Пользователю:

                Compress_struct_.total_WritingBytes = Compress_struct_.total_WritingBytes + Compress_struct_.output.pos;

                check_ResizeBuff(string_CompressedResult, Compress_struct_.total_WritingBytes, CHUNK_TailSize);     //Проверяем нужно ли расширить размер "string_CompressedResult" с учетом индекса "total_WritingBytes".

                Compress_struct_.output = { &string_CompressedResult[Compress_struct_.total_WritingBytes], CHUNK_TailSize, 0 };   //Записываем в структуру ZSTD_outBuffer - данные: указатель на буффер куда нужно помещать сжатые данные, размер этого буффера и позиция в буффере, в данном случае позизиция всегда нулевая. ВАЖНО!!!: После вызова "ZSTD_compressStream2" она внутри у себя обновит третье поле .pos - куда запишет кол-во сжатых байт и записанных по указанному указателю.
            }
            //----------------------------------------------Вызываем Пользовательский колбек:Начало--------------------------------

        }
        //***************************************************************************************************************************************************************



        return result_flag::OK;

    }
    inline const result_flag Run_Compress_EndDirective_Handler(std::string& string_CompressedResult)
    {

        //Из документации: "Вы должны продолжать вызывать ZSTD_compressStream2() с ZSTD_e_end до тех пор, пока не будет возвращено значение 0, после чего вы можете начать новый кадр." (с) https://facebook.github.io/zstd/zstd_manual.html


        //-------------------------------------------------------------------------------------
        Compress_struct_.input = { 0, 0, 0 };       //Так как все данные из входящего буффера данных, которые нужно сжать мы уже обработали, то теоертически он нафиг уже не нужон этот ваш входящий буффер.
        //-------------------------------------------------------------------------------------



        //---------------------------------------------------------
        Compress_struct_.output = { &string_CompressedResult[Compress_struct_.total_WritingBytes], Compress_struct_.CHUNK_SIZE_this, 0 };   //Записываем в структуру ZSTD_outBuffer - данные: указатель на буффер куда нужно помещать сжатые данные, размер этого буффера и позиция в буффере, в данном случае позизиция всегда нулевая. ВАЖНО!!!: После вызова "ZSTD_compressStream2" она внутри у себя обновит третье поле .pos - куда запишет кол-во сжатых байт и записанных по указанному указателю.
        //---------------------------------------------------------




        //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        for (;;)
        {

            //-------------------------------------------------ZSTD_compressStream2:Начало------------------------------------------------------------------

            const size_t ZSTD_compressStream2_FinalySize = ZSTD_compressStream2(Compress_struct_.ZSTD_CStream_, &(Compress_struct_.output), &(Compress_struct_.input), ZSTD_e_end);               //Собстно вызываем функцию сжатия.


            //```````````````````````````````````````````````````````````````````````
            unsigned int status_error = ZSTD_isError(ZSTD_compressStream2_FinalySize);  //Проверяем последний вызов на наличие ошибки.

            if (status_error != 0)
            {
                ErrorName = "ZSTD_compressStream2: " + std::string(ZSTD_getErrorName(ZSTD_compressStream2_FinalySize));

                ZSTD_CCtx_reset(Compress_struct_.ZSTD_CStream_, ZSTD_reset_session_and_parameters);

                return result_flag::Zstadart_error;
            }
            //```````````````````````````````````````````````````````````````````````

            //output.pos - теперь тут обвновленные данные, которые функция "ZSTD_compressStream2" занесла в это поле, которое говорит о том, сколько байт было записано по указателю "output.dst".    

            //-------------------------------------------------ZSTD_compressStream2:Конец------------------------------------------------------------------


            //----------------------------------------------Вызываем Пользовательский колбек:Начало--------------------------------
            if (Compress_struct_.output.pos != 0)
            {
                //Значит ZSTD_compressStream2 - записала часть каких то сжатых данных, отправим их Пользователю:

                //Значит конечно сжатие данных еще Не Завершено.

                Compress_struct_.total_WritingBytes = Compress_struct_.total_WritingBytes + Compress_struct_.output.pos;

                check_ResizeBuff(string_CompressedResult, Compress_struct_.total_WritingBytes, Compress_struct_.CHUNK_SIZE_this);     //Проверяем нужно ли расширить размер "string_CompressedResult" с учетом индекса "total_WritingBytes".

                Compress_struct_.output = { &string_CompressedResult[Compress_struct_.total_WritingBytes], Compress_struct_.CHUNK_SIZE_this, 0 };     //Записываем в структуру ZSTD_outBuffer - данные: указатель на буффер куда нужно помещать сжатые данные, размер этого буффера и позиция в буффере, в данном случае позизиция всегда нулевая. ВАЖНО!!!: После вызова "ZSTD_compressStream2" она внутри у себя обновит третье поле .pos - куда запишет кол-во сжатых байт и записанных по указанному указателю.
            }
            //----------------------------------------------Вызываем Пользовательский колбек:Начало--------------------------------



            //------------------------------------------------------------------------------------
            if (ZSTD_compressStream2_FinalySize == 0)
            {
                return result_flag::OK;
            }
            //------------------------------------------------------------------------------------


        }
        //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


        return result_flag::OK;

    }


    const result_flag Run_Uncompress_(const size_t CHUNK_SIZE, const size_t size_BeforeResize, const char* PointerToData_WhichShouldBe_Uncompressed, const size_t DataSize_WhichShouldBe_Uncompressed, std::string& string_UnUncompressedResult)
    {



        //----------------------------------------------------------------Расчитаем целое кол-во Чанков и хвост:Начало-----------------------------------------------------------------

        //Короче, предположим пользовтаель указал указатель на данные, которые нужно сжать и указал их размер в 123 байта, и размер Чанка в 10 байт.
        //Итого получается, что у нас есть 123/10 = 12 целых проходов по 10 байт и 3 байтовый хвост, который неполучится оброботать 10 байтовым Чанком, а значит этот хвост прижется обработать отдельно от основного цикла.

        //ИЛИ ЖЕ можно просто ту по в цикле каждую итерацию проверять, сколько байт осталось обработать и сравнивать их с 10 байтовых Чанком, но, как по мне это просто бессмысленное трата на сравнение - ради одного единсвенного хвоста.

        //----------------------------------------------------------------------------------
        size_t Loop_number;

        if (CHUNK_SIZE > DataSize_WhichShouldBe_Uncompressed)
        {
            //Значит указанный CHUNK_SIZE больше, чем размер самого буффера "PointerToData_WhichShouldBe_Uncompressed".

            Uncompress_struct_.CHUNK_SIZE_this = DataSize_WhichShouldBe_Uncompressed;       //Значит ставим Размер чанка равным размеру буффера данных которые нужно сжать.
            Uncompress_struct_.CHUNK_TailSize_this = 0;                                       //Хвоста значит нет.
            Loop_number = 1;
        }
        else
        {
            Loop_number = DataSize_WhichShouldBe_Uncompressed / CHUNK_SIZE;  //В типе size_t любая дробная часть автоматчиески отбросится, поэтому получим чистое целое.

            Uncompress_struct_.CHUNK_SIZE_this = CHUNK_SIZE;
            Uncompress_struct_.CHUNK_TailSize_this = DataSize_WhichShouldBe_Uncompressed - Loop_number * CHUNK_SIZE;  //Расчитаем размер хвоста.
            Loop_number = DataSize_WhichShouldBe_Uncompressed / CHUNK_SIZE;                        //В типе size_t любая дробная часть автоматчиески отбросится, поэтому получим чистое целое.
        }
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------Расчитаем целое кол-во Чанков и хвост:Конец-----------------------------------------------------------------



        //------------------------------------------------------
        try { string_UnUncompressedResult.resize(size_BeforeResize + DataSize_WhichShouldBe_Uncompressed); }
        catch (const std::bad_alloc& e) { ErrorName = e.what(); return  result_flag::bad_alloc; }  //Выделяем память под выходной буффер, в который будет записыватся частичный результат сжатия.
        //------------------------------------------------------


        //-------------------------------------------------------------------------------------------------------------
        /*
        typedef struct ZSTD_outBuffer_s
        {
        void* dst;         // start of output buffer
        size_t size;       // < size of output buffer
        size_t pos;        // < position where writing stopped. Will be updated. Necessarily 0 <= pos <= size
        } ZSTD_outBuffer;
        //-------------------------------------------------------------------------------------------------------------
        typedef struct ZSTD_inBuffer_s
        {
            const void* src;    // start of input buffer
            size_t size;        //  size of input buffer
            size_t pos;         // position where reading stopped. Will be updated. Necessarily 0 <= pos <= size
        } ZSTD_inBuffer;
        */
        //-------------------------------------------------------------------------------------------------------------



        //-----------------------------------
        size_t total_ReadingBytes = 0;                       //Суммарно кол-во прочитанных байт, которые нужно сжать, то есть кол-во байт, которые нужно сжать - уже было обработано и сжато.
        size_t total_WritingBytes = size_BeforeResize;       //Суммарно кол-во Сжатых байт в моменте. Нужно для определения смещения в "string_UncompressedResult"
        //-----------------------------------



        //-------------------------------------------------------------------------------------------
        const result_flag result_1 = Run_Uncompress_MainLoop(Loop_number, total_ReadingBytes, total_WritingBytes, Uncompress_struct_.CHUNK_SIZE_this, PointerToData_WhichShouldBe_Uncompressed, string_UnUncompressedResult); if (result_1 != result_flag::OK) { string_UnUncompressedResult.resize(size_BeforeResize);  return result_1; }

        //-------------------------------------------------------Обработаем хвост:Начало-------------------------------------------
        if (Uncompress_struct_.CHUNK_TailSize_this != 0)
        {
            const result_flag result_2 = Run_Uncompress_Tail_Handler(total_ReadingBytes, total_WritingBytes, Uncompress_struct_.CHUNK_TailSize_this, PointerToData_WhichShouldBe_Uncompressed, string_UnUncompressedResult);   if (result_2 != result_flag::OK) { string_UnUncompressedResult.resize(size_BeforeResize); return result_2; }
        }
        //-------------------------------------------------------Обработаем хвост:Конец-------------------------------------------



        //-----------------------------------------------------------
        string_UnUncompressedResult.resize(total_WritingBytes);        //Корректируем размер под актульные данные.
        string_UnUncompressedResult.shrink_to_fit();
        //-----------------------------------------------------------



        return result_flag::OK;
    }
    inline const result_flag Run_Uncompress_MainLoop(const size_t Loop_number, size_t& total_ReadingBytes, size_t& total_WritingBytes, const size_t CHUNK_SIZE, const char* PointerToData_WhichShouldBe_Uncompressed, std::string& string_UnUncompressedResult)
    {


        Uncompress_struct_.output = { &string_UnUncompressedResult[total_WritingBytes], CHUNK_SIZE, 0 };   //Записываем в структуру ZSTD_outBuffer - данные: указатель на буффер куда нужно помещать сжатые данные, размер этого буффера и позиция в буффере, в данном случае позизиция всегда нулевая. ВАЖНО!!!: После вызова "ZSTD_decompressStream" она внутри у себя обновит третье поле .pos - куда запишет кол-во сжатых байт и записанных по указанному указателю.



        //***************************************************************************************************************************************************************************

        for (size_t i = 0; i < Loop_number; i++)
        {


            //-------------------------------------------------------------------------------------
            Uncompress_struct_.input = { PointerToData_WhichShouldBe_Uncompressed + total_ReadingBytes, CHUNK_SIZE, 0 };      //Указываем указатель на буффер с данными, который нужно сжать и размер данных, которые нужно сжать. Третий параметр функция "ZSTD_decompressStream" обновляет у себя внутри указывая на кол-по прочитанных байт по указаннмоу указателю в кол-ве "CHUNK_SIZE" байт. ТО ЕСТЬ, функцию "ZSTD_decompressStream" нужно вызывать в цикле до тех пор, пока третий параметр по значению не станет равным == CHUNK_SIZE - что будет означать, что данная порция данных прочитана и сжата. ПОСЛЕ ЧЕГО если есть еще одна порция данных для сжатия - то смещаем или меняем указатель на новые данные которые нужно сжать, устанавливаем нужный размер и ТРЕТИЙ ПАРАМТР ОПЯТЬ ЗАНУЛЯЕТСЯ, чтобы функция начала читать с первого байта по указанном указателю.
            //-------------------------------------------------------------------------------------



            //***************************************************************************************************************************************************************
            while (Uncompress_struct_.input.pos < CHUNK_SIZE)
            {

                //-------------------------------------------------ZSTD_decompressStream:Начало------------------------------------------------------------------

                const size_t ZSTD_decompressStream_FinalySize = ZSTD_decompressStream(Uncompress_struct_.ZSTD_DStream_, &(Uncompress_struct_.output), &(Uncompress_struct_.input));               //Собстно вызываем функцию сжатия.


                //```````````````````````````````````````````````````````````````````````
                unsigned int status_error = ZSTD_isError(ZSTD_decompressStream_FinalySize);  //Проверяем последний вызов на наличие ошибки.

                if (status_error != 0)
                {
                    ErrorName = "ZSTD_decompressStream: " + std::string(ZSTD_getErrorName(ZSTD_decompressStream_FinalySize));

                    ZSTD_DCtx_reset(Uncompress_struct_.ZSTD_DStream_, ZSTD_reset_session_and_parameters);

                    return result_flag::Zstadart_error;
                }
                //```````````````````````````````````````````````````````````````````````

                //output.pos - теперь тут обвновленные данные, которые функция "ZSTD_decompressStream" занесла в это поле, которое говорит о том, сколько байт было записано по указателю "output.dst".
                //input.pos  - теперь тут обвновленные данные, которые функция "ZSTD_decompressStream" занесла в это поле, которое говорит о том, скольок байт было прочитано из указателя на данные которые нужно сжать.

                //-------------------------------------------------ZSTD_decompressStream:Конец------------------------------------------------------------------



                //----------------------------------------------Вызываем Пользовательский колбек:Начало--------------------------------
                if (Uncompress_struct_.output.pos != 0)
                {
                    //Значит ZSTD_decompressStream - записала часть каких то сжатых данных.

                    total_WritingBytes = total_WritingBytes + Uncompress_struct_.output.pos;

                    check_ResizeBuff(string_UnUncompressedResult, total_WritingBytes, CHUNK_SIZE);     //Проверяем нужно ли расширить размер "string_CompressedResult" с учетом индекса "total_WritingBytes".

                    Uncompress_struct_.output = { &string_UnUncompressedResult[total_WritingBytes], CHUNK_SIZE, 0 };   //Записываем в структуру ZSTD_outBuffer - данные: указатель на буффер куда нужно помещать сжатые данные, размер этого буффера и позиция в буффере, в данном случае позизиция всегда нулевая. ВАЖНО!!!: После вызова "ZSTD_decompressStream" она внутри у себя обновит третье поле .pos - куда запишет кол-во сжатых байт и записанных по указанному указателю.
                }
                //----------------------------------------------Вызываем Пользовательский колбек:Начало--------------------------------

            }
            //***************************************************************************************************************************************************************


            total_ReadingBytes = total_ReadingBytes + CHUNK_SIZE;   //Суммируем обработанную порцию данных, которые нужно сжать, чтобы потом сместить его на это значение, для дальнейшей порции обработки данных.

        }

        //***************************************************************************************************************************************************************************



        return result_flag::OK;
    }
    inline const result_flag Run_Uncompress_Tail_Handler(const size_t total_ReadingBytes, size_t& total_WritingBytes, const size_t CHUNK_TailSize, const char* PointerToData_WhichShouldBe_Uncompressed, std::string& string_UnUncompressedResult)
    {


        //-------------------------------------------------------------------------------------
        Uncompress_struct_.input = { PointerToData_WhichShouldBe_Uncompressed + total_ReadingBytes, CHUNK_TailSize, 0 };      //Указываем указатель на буффер с данными, который нужно сжать и размер данных, которые нужно сжать. Третий параметр функция "ZSTD_decompressStream" обновляет у себя внутри указывая на кол-по прочитанных байт по указаннмоу указателю в кол-ве "CHUNK_SIZE" байт. ТО ЕСТЬ, функцию "ZSTD_decompressStream" нужно вызывать в цикле до тех пор, пока третий параметр по значению не станет равным == CHUNK_SIZE - что будет означать, что данная порция данных прочитана и сжата. ПОСЛЕ ЧЕГО если есть еще одна порция данных для сжатия - то смещаем или меняем указатель на новые данные которые нужно сжать, устанавливаем нужный размер и ТРЕТИЙ ПАРАМТР ОПЯТЬ ЗАНУЛЯЕТСЯ, чтобы функция начала читать с первого байта по указанном указателю.
        //-------------------------------------------------------------------------------------


        Uncompress_struct_.output = { &string_UnUncompressedResult[total_WritingBytes], CHUNK_TailSize, 0 };   //Записываем в структуру ZSTD_outBuffer - данные: указатель на буффер куда нужно помещать сжатые данные, размер этого буффера и позиция в буффере, в данном случае позизиция всегда нулевая. ВАЖНО!!!: После вызова "ZSTD_decompressStream" она внутри у себя обновит третье поле .pos - куда запишет кол-во сжатых байт и записанных по указанному указателю.


        //***************************************************************************************************************************************************************
        while (Uncompress_struct_.input.pos < CHUNK_TailSize)
        {

            //-------------------------------------------------ZSTD_decompressStream:Начало------------------------------------------------------------------

            const size_t ZSTD_decompressStream_FinalySize = ZSTD_decompressStream(Uncompress_struct_.ZSTD_DStream_, &(Uncompress_struct_.output), &(Uncompress_struct_.input));               //Собстно вызываем функцию сжатия.


            //```````````````````````````````````````````````````````````````````````
            unsigned int status_error = ZSTD_isError(ZSTD_decompressStream_FinalySize);  //Проверяем последний вызов на наличие ошибки.

            if (status_error != 0)
            {
                ErrorName = "ZSTD_decompressStream: " + std::string(ZSTD_getErrorName(ZSTD_decompressStream_FinalySize));

                ZSTD_DCtx_reset(Uncompress_struct_.ZSTD_DStream_, ZSTD_reset_session_and_parameters);

                return result_flag::Zstadart_error;
            }
            //```````````````````````````````````````````````````````````````````````

            //output.pos - теперь тут обвновленные данные, которые функция "ZSTD_decompressStream" занесла в это поле, которое говорит о том, сколько байт было записано по указателю "output.dst".
            //input.pos  - теперь тут обвновленные данные, которые функция "ZSTD_decompressStream" занесла в это поле, которое говорит о том, скольок байт было прочитано из указателя на данные которые нужно сжать.

            //-------------------------------------------------ZSTD_decompressStream:Конец------------------------------------------------------------------



            //----------------------------------------------Вызываем Пользовательский колбек:Начало--------------------------------
            if (Uncompress_struct_.output.pos != 0)
            {
                //Значит ZSTD_decompressStream - записала часть каких то сжатых данных, отправим их Пользователю:

                total_WritingBytes = total_WritingBytes + Uncompress_struct_.output.pos;

                check_ResizeBuff(string_UnUncompressedResult, total_WritingBytes, CHUNK_TailSize);     //Проверяем нужно ли расширить размер "string_CompressedResult" с учетом индекса "total_WritingBytes".

                Uncompress_struct_.output = { &string_UnUncompressedResult[total_WritingBytes], CHUNK_TailSize, 0 };   //Записываем в структуру ZSTD_outBuffer - данные: указатель на буффер куда нужно помещать сжатые данные, размер этого буффера и позиция в буффере, в данном случае позизиция всегда нулевая. ВАЖНО!!!: После вызова "ZSTD_decompressStream" она внутри у себя обновит третье поле .pos - куда запишет кол-во сжатых байт и записанных по указанному указателю.
            }
            //----------------------------------------------Вызываем Пользовательский колбек:Начало--------------------------------

        }
        //***************************************************************************************************************************************************************


        return result_flag::OK;

    }


    inline void check_ResizeBuff(std::string& string_Buff, const size_t total_WritingBytes, const size_t CHUNK_SIZE)
    {

        if (string_Buff.size() <= (total_WritingBytes + CHUNK_SIZE))
        {
            //Значит "total_WritingBytes" индекс уже вышел за пределы реального выделнной памяти под "string_Buff" придется расширять, расширим сразу на 10*CHUNK_SIZE:

            string_Buff.resize(string_Buff.size() + 10 * CHUNK_SIZE);
        }

    }

};
