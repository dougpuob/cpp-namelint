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
      FileName                = 0 # 0: Default (UpperCamel) \n\
                                  # 1: UpperCamel           \n\
                                  # 3: lower_snake          \n\
                                                            \n\
      FunctionName            = 5 # 0: Default (UpperCamel) \n\
                                  # 1: UpperCamel           \n\
                                  # 2: lowerCamel           \n\
                                  # 3: lower_snake          \n\
                                  # 5: UPPER_SNAKE          \n\
                                                            \n\
      VariableName            = 5 # 0: Default (UpperCamel) \n\
                                  # 1: UpperCamel           \n\
                                  # 2: lowerCamel           \n\
                                  # 3: lower_snake          \n\
                                  # 4: Hungarian            \n\
                                                            \n\
      ClassName               = 5 # 0: Default (UpperCamel) \n\
                                  # 1: UpperCamel           \n\
                                  # 2: lowerCamel           \n\
                                  # 3: lower_snake          \n\
                                  # 5: UPPER_SNAKE          \n\
                                                            \n\
      EnumTagName             = 5 # 0: Default (UpperCamel) \n\
                                  # 1: UpperCamel           \n\
                                  # 2: lowerCamel           \n\
                                  # 3: lower_snake          \n\
                                  # 5: UPPER_SNAKE          \n\
                                                            \n\
      EnumValueName           = 5 # 0: Default (UpperCamel) \n\
                                  # 1: UpperCamel           \n\
                                  # 2: lowerCamel           \n\
                                  # 3: lower_snake          \n\
                                  # 5: UPPER_SNAKE          \n\
                                                            \n\
      StructTagName           = 5 # 0: Default (UpperCamel) \n\
                                  # 1: UpperCamel           \n\
                                  # 2: lowerCamel           \n\
                                  # 3: lower_snake          \n\
                                  # 5: UPPER_SNAKE          \n\
                                                            \n\
      StructValueName         = 5 # 0: Default (UpperCamel) \n\
                                  # 1: UpperCamel           \n\
                                  # 2: lowerCamel           \n\
                                  # 3: lower_snake          \n\
                                  # 4: Hungarian            \n\
                                  # 5: UPPER_SNAKE          \n\
    ";

namespace RunCheckUpperSnake {

TEST(Variable, Integers) {
  MemoBoard &MemoBoard = AppCxt::getInstance().MemoBoard;
  MemoBoard.Clear();

  string ErrorReason;
  MemoBoard.Config.LoadStream(ConfigToml, ErrorReason);
  shared_ptr<ConfigData> pCfgData = MemoBoard.Config.GetData();

  const string SourceCode = " \n\
        int USB_LOW_SPEED   = 1;    \n\
        int USB_FULL_SPEED  = 2;    \n\
        int USB_HIGH_SPEED  = 3;    \n\
        int USB_SUPER_SPEED = 4;    \n\
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
        int* USB_LOW_SPEED   = NULL;    \n\
        int* USB_FULL_SPEED  = NULL;    \n\
        int* USB_HIGH_SPEED  = NULL;    \n\
        int* USB_SUPER_SPEED = NULL;    \n\
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

  const string SourceCode = "      \n\
        int USB_LOW_SPEED[8]   = {0};  \n\
        int USB_FULL_SPEED[8]  = {0};  \n\
        int USB_HIGH_SPEED[8]  = {0};  \n\
        int USB_SUPER_SPEED[8] = {0};  \n\
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

  const string SourceCode = "       \n\
        typedef enum _USB_DEVICE_SPEED {  \n\
            USB_LOW_SPEED = 0,            \n\
            USB_FULL_SPEED,               \n\
            USB_HIGH_SPEED,               \n\
            USB_SUPER_SPEED               \n\
        } USB_DEVICE_SPEED;               \n\
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

  const string SourceCode = "                 \n\
        typedef struct _USB_ENDPOINT_DESCRIPTOR {   \n\
            UCHAR   LENGTH;                         \n\
            UCHAR   DESCRIPTOR_TYPE;                \n\
            UCHAR   ENDPOINT_ADDRESS;               \n\
            UCHAR   ATTRIBUTES;                     \n\
            USHORT  MAX_PACKET_SIZE;                \n\
            UCHAR   INTERVAL;                       \n\
        } USB_ENDPOINT_DESCRIPTOR;                  \n\
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

  const string SourceCode = "       \n\
        int (*FN_NAME_1)(int, int);     \n\
        int (*FN_NAME_2)(int A, int B); \n\
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

  const string SourceCode = "                       \n\
        void *                                            \n\
        MEM_CPY (void *DEST, const void *SRC, size_t LEN) \n\
        {                                                 \n\
          char *D = DEST;                                 \n\
          const char *S = SRC;                            \n\
          while (LEN--)                                   \n\
            *D++ = *S++;                                  \n\
          return DEST;                                    \n\
        }                                                 \n\
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
        class DATA_CLASS                                    \n\
        {                                                   \n\
        private:                                            \n\
            int m_YEAR;                                     \n\
            int m_MONTH;                                    \n\
            int m_DAY;                                      \n\
                                                            \n\
        public:                                             \n\
            DATA_CLASS(int YEAR, int MONTH, int DAY)        \n\
            {                                               \n\
                SET_DATA(YEAR, MONTH, DAY);                 \n\
            }                                               \n\
                                                            \n\
            ~DATA_CLASS() {};                               \n\
                                                            \n\
            void SET_DATA(int YEAR, int MONTH, int DAY)     \n\
            {                                               \n\
                m_YEAR = YEAR;                              \n\
                m_MONTH = MONTH;                            \n\
                m_DAY = DAY;                                \n\
            }                                               \n\
                                                            \n\
            int GET_YEAR()  { return m_YEAR;  }             \n\
            int GET_MONTH() { return m_MONTH; }             \n\
            int GET_DAY()   { return m_DAY;  }              \n\
        };                                                  \n\
        ";

  pCfgData->General.IgnoredList.VariablePrefix.push_back("m_");

  EXPECT_EQ(true, 0 == RunCheckFormStream(MemoBoard, SourceCode));

  EXPECT_EQ(true, 0 == MemoBoard.Checked.nFile);
  EXPECT_EQ(true, 6 == MemoBoard.Checked.nFunction);
  EXPECT_EQ(true, 6 == MemoBoard.Checked.nParameter);
  EXPECT_EQ(true, 3 == MemoBoard.Checked.nVariable);
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

  const string SourceCode = "#define GET_MIN(X, Y) ((X) < (Y) ? (X) : (Y))";

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

} // namespace RunCheckUpperSnake