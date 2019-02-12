#pragma once

const int PCX_HEADER_SIZE = 128;
const int PCX_HEADER_FLAG = 10;
const int PCX_HEADER_ENCODE = 1;
const int PCX_VER_SUPPORT = 5;

#pragma pack(1)
typedef struct         		// pcx文件头
{
    BYTE flag;				// 标记
    BYTE version;			// 版本号
    BYTE encodeing;			// 编码方式
    BYTE bitsPrePixel;		// 平面像素位数
    WORD xMin;				// 最小X
    WORD yMin;				// 最小Y
    WORD xMax;				// 最大X
    WORD yMax;				// 最大Y
    WORD hRes;				// 水平分辨率
    WORD vRes;				// 垂直分辨率
    BYTE palette[48];		// 16色调色板
    BYTE reserved;			// 保留
    BYTE planes;			// 平面数
    WORD bytesPreLine;		// 每行字节数
    WORD paletteType;		// 调色板类型。1：彩色或黑白，2：灰度
    BYTE filler[58];
}PCX_HEADER, *PPCX_HEADER;
#pragma pack()

class CPcxFileHeader
{
public:
    CPcxFileHeader();
    ~CPcxFileHeader();

    bool ReadHeader(std::ifstream& file);
    bool WriteHeader(std::ofstream& file);
    int GetBytesPreLine() const { return m_data.bytesPreLine; }
    void SetBytesPreLine(int bytesPreLine) { m_data.bytesPreLine = bytesPreLine; }
    int GetBitsPrePixel() const { return m_data.bitsPrePixel; }
    void SetBitsPrePixel(int bitsPrePixel) { m_data.bitsPrePixel = bitsPrePixel; }
    int GetBmpWidth() const { return (m_data.xMax - m_data.xMin + 1); }
    void SetBmpWidth(int width);
    int GetBmpHeight() const { return (m_data.yMax - m_data.yMin + 1); }
    void SetBmpHeight(int height);
    int GetPlanes() const { return m_data.planes; }
    int GetVersion() const { return m_data.version; }

protected:
    PCX_HEADER m_data;
};

