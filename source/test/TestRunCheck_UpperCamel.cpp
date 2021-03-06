#include <vector>

#include <gtest/gtest.h>

#include "../Common.h"
#include "../TraceMemo.h"

using namespace namelint;

const string ConfigToml = "\
    [General.Options]                                       \n\
      Version                 = 0.3                         \n\
      CheckFileName           = false                       \n\
      CheckVariableName       = true                        \n\
      CheckFunctionName       = true                        \n\
      CheckEnum               = true                        \n\
      CheckStruct             = true                        \n\
      CheckClass              = true                        \n\
      AllowedPrintResult      = false                       \n\
      AllowedWriteJsonResult  = false                       \n\
      AllowedUnderscopeChar   = false                       \n\
      AllowedArrayAffected    = false                       \n\
                                                            \n\
    [General.Rules]                                         \n\
      FileName                = 1 # 0: Default (UpperCamel) \n\
                                  # 1: UpperCamel           \n\
                                  # 3: lower_snake          \n\
                                                            \n\
      FunctionName            = 1 # 0: Default (UpperCamel) \n\
                                  # 1: UpperCamel           \n\
                                  # 2: lowerCamel           \n\
                                  # 3: lower_snake          \n\
                                                            \n\
      VariableName            = 1 # 0: Default (UpperCamel) \n\
                                  # 1: UpperCamel           \n\
                                  # 2: lowerCamel           \n\
                                  # 3: lower_snake          \n\
                                  # 4: Hungarian            \n\
                                                            \n\
      ClassName               = 1 # 0: Default (UpperCamel) \n\
                                  # 1: UpperCamel           \n\
                                  # 2: lowerCamel           \n\
                                  # 3: lower_snake          \n\
                                  # 5: UPPER_SNAKE          \n\
                                                            \n\
      EnumTagName             = 1 # 0: Default (UpperCamel) \n\
                                  # 1: UpperCamel           \n\
                                  # 2: lowerCamel           \n\
                                  # 3: lower_snake          \n\
                                  # 5: UPPER_SNAKE          \n\
                                                            \n\
      EnumValueName           = 1 # 0: Default (UpperCamel) \n\
                                  # 1: UpperCamel           \n\
                                  # 2: lowerCamel           \n\
                                  # 3: lower_snake          \n\
                                  # 5: UPPER_SNAKE          \n\
                                                            \n\
      StructTagName           = 1 # 0: Default (UpperCamel) \n\
                                  # 1: UpperCamel           \n\
                                  # 2: lowerCamel           \n\
                                  # 3: lower_snake          \n\
                                  # 5: UPPER_SNAKE          \n\
                                                            \n\
      StructValueName         = 1 # 0: Default (UpperCamel) \n\
                                  # 1: UpperCamel           \n\
                                  # 2: lowerCamel           \n\
                                  # 3: lower_snake          \n\
                                  # 4: Hungarian            \n\
                                  # 5: UPPER_SNAKE          \n\
    ";

namespace RunCheckUpperCamel {

TEST(Variable, Integers) {
  MemoBoard &MemoBoard = AppCxt::getInstance().MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);
  shared_ptr<ConfigData> pCfgData = MemoBoard.Config.GetData();

  const string SourceCode = " \n\
        int UsbLowSpeed   = 1;  \n\
        int UsbFullSpeed  = 2   \n\
        int UsbHighSpeed  = 3;  \n\
        int UsbSuperSpeed = 4;  \n\
    ";

  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));

  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nParameter);
  EXPECT_EQ(true, 4 == MemoBoard.Checked.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nUnion);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nClass);

  EXPECT_EQ(true, 0 == MemoBoard.Error.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nParameter);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nUnion);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nClass);
}

TEST(Variable, IntegerPointers) {
  MemoBoard &MemoBoard = AppCxt::getInstance().MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);
  shared_ptr<ConfigData> pCfgData = MemoBoard.Config.GetData();

  const string SourceCode = "       \n\
        int* UsbLowSpeed   = NULL;  \n\
        int* UsbFullSpeed  = NULL   \n\
        int* UsbHighSpeed  = NULL;  \n\
        int* UsbSuperSpeed = NULL;  \n\
    ";

  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));

  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nParameter);
  EXPECT_EQ(true, 4 == MemoBoard.Checked.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nUnion);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nClass);

  EXPECT_EQ(true, 0 == MemoBoard.Error.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nParameter);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nUnion);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nClass);
}

TEST(Variable, IntegerArraies) {
  MemoBoard &MemoBoard = AppCxt::getInstance().MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);
  shared_ptr<ConfigData> pCfgData = MemoBoard.Config.GetData();

  const string SourceCode = "        \n\
        int UsbLowSpeed[8]   = {0};  \n\
        int UsbFullSpeed[8]  = {0}   \n\
        int UsbHighSpeed[8]  = {0};  \n\
        int UsbSuperSpeed[8] = {0};  \n\
    ";

  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));

  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nParameter);
  EXPECT_EQ(true, 4 == MemoBoard.Checked.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nUnion);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nClass);

  EXPECT_EQ(true, 0 == MemoBoard.Error.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nParameter);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nUnion);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nClass);
}

TEST(Enum, UsbEndpointDescriptor) {
  MemoBoard &MemoBoard = AppCxt::getInstance().MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);
  shared_ptr<ConfigData> pCfgData = MemoBoard.Config.GetData();

  const string SourceCode = "           \n\
        typedef enum _UsbDeviceSpeed {  \n\
            UsbLowSpeed = 0,            \n\
            UsbFullSpeed,               \n\
            UsbHighSpeed,               \n\
            UsbSuperSpeed               \n\
        } UsbDeviceSpeed;               \n\
    ";

  pCfgData->General.IgnoredList.EnumTagPrefix.push_back("_");
  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));

  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nParameter);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nVariable);
  EXPECT_EQ(true, 5 == MemoBoard.Checked.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nUnion);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nClass);

  EXPECT_EQ(true, 0 == MemoBoard.Error.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nParameter);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nUnion);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nClass);
}

TEST(Struct, UsbEndpointDescriptor) {
  MemoBoard &MemoBoard = AppCxt::getInstance().MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);
  shared_ptr<ConfigData> pCfgData = MemoBoard.Config.GetData();

  const string SourceCode = "                      \n\
        typedef struct _UsbEndpointDescriptor {    \n\
            UCHAR   Length;                        \n\
            UCHAR   DescriptorType;                \n\
            UCHAR   EndpointAddress;               \n\
            UCHAR   Attributes;                    \n\
            USHORT  MaxPacketSize;                 \n\
            UCHAR   Interval;                      \n\
        } UsbEndpointDescriptor;                   \n\
    ";

  pCfgData->General.IgnoredList.StructTagPrefix.push_back("_");

  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));

  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nParameter);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nEnum);
  EXPECT_EQ(true, 7 == MemoBoard.Checked.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nUnion);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nClass);

  EXPECT_EQ(true, 0 == MemoBoard.Error.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nParameter);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nUnion);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nClass);
}

TEST(Function, FnPtr) {
  MemoBoard &MemoBoard = AppCxt::getInstance().MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);
  shared_ptr<ConfigData> pCfgData = MemoBoard.Config.GetData();

  const string SourceCode = "           \n\
        int (*FnName1)(int, int);       \n\
        int (*FnName2)(int A, int B);   \n\
        ";

  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));

  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFunction);
  EXPECT_EQ(true, 2 == MemoBoard.Checked.nParameter);
  EXPECT_EQ(true, 2 == MemoBoard.Checked.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nUnion);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nClass);

  EXPECT_EQ(true, 0 == MemoBoard.Error.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nParameter);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nUnion);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nClass);
}

TEST(Function, MemCpy) {
  MemoBoard &MemoBoard = AppCxt::getInstance().MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);
  shared_ptr<ConfigData> pCfgData = MemoBoard.Config.GetData();

  const string SourceCode = "                            \n\
        void *                                           \n\
        MemCpy (void *Dest, const void *Src, size_t Len) \n\
        {                                                \n\
          char *D = Dest;                                \n\
          const char *S = Src;                           \n\
          while (Len--)                                  \n\
            *D++ = *S++;                                 \n\
          return Dest;                                   \n\
        }                                                \n\
        ";

  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));

  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFile);
  EXPECT_EQ(true, 1 == MemoBoard.Checked.nFunction);
  EXPECT_EQ(true, 3 == MemoBoard.Checked.nParameter);
  EXPECT_EQ(true, 2 == MemoBoard.Checked.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nUnion);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nClass);

  EXPECT_EQ(true, 0 == MemoBoard.Error.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nParameter);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nUnion);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nClass);
}

TEST(Class, DataClass) {
  MemoBoard &MemoBoard = AppCxt::getInstance().MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);
  shared_ptr<ConfigData> pCfgData = MemoBoard.Config.GetData();

  const string SourceCode = "                               \n\
        class DateClass                                     \n\
        {                                                   \n\
        private:                                            \n\
            int m_Year;                                     \n\
            int m_Month;                                    \n\
            int m_Dday;                                     \n\
            int m_Dday1;                                    \n\
                                                            \n\
        public:                                             \n\
            DateClass(int Year, int Month, int Day)         \n\
            {                                               \n\
                SetDate(Year, Month, Day);                  \n\
            }                                               \n\
                                                            \n\
            ~DateClass() {};                                \n\
                                                            \n\
            void SetDate(int Year, int Month, int Day)      \n\
            {                                               \n\
                m_Year = Year;                              \n\
                m_Month = Month;                            \n\
                m_Dday = Day;                               \n\
            }                                               \n\
                                                            \n\
            int GetYear()  { return m_Year;  }              \n\
            int GetMonth() { return m_Month; }              \n\
            int GetDay()   { return m_Dday;  }              \n\
        };                                                  \n\
        ";

  pCfgData->General.IgnoredList.VariablePrefix.push_back("m_");

  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));

  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFile);
  EXPECT_EQ(true, 6 == MemoBoard.Checked.nFunction);
  EXPECT_EQ(true, 6 == MemoBoard.Checked.nParameter);
  EXPECT_EQ(true, 4 == MemoBoard.Checked.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nUnion);
  EXPECT_EQ(true, 1 == MemoBoard.Checked.nClass);

  EXPECT_EQ(true, 0 == MemoBoard.Error.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nParameter);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nUnion);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nClass);
}

// TODO: Seems this function never be supported.
TEST(MacroFunction, GetMin) {
  MemoBoard &MemoBoard = AppCxt::getInstance().MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);
  shared_ptr<ConfigData> pCfgData = MemoBoard.Config.GetData();

  const string SourceCode = "#define GetMin(X, Y) ((X) < (Y) ? (X) : (Y))";

  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));

  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nParameter);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nUnion);
  EXPECT_EQ(true, 0 == MemoBoard.Checked.nClass);

  EXPECT_EQ(true, 0 == MemoBoard.Error.nFile);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nFunction);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nParameter);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nVariable);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nEnum);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nStruct);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nUnion);
  EXPECT_EQ(true, 0 == MemoBoard.Error.nClass);
}

} // namespace RunCheckUpperCamel