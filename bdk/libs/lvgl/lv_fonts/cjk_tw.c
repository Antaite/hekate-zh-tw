/*
 * 繁體中文字型（由 tools/zh_tw/gen_cjk.py 自動產生，請勿手動修改）
 * 字型來源：Noto Sans CJK TC（SIL Open Font License 1.1）
 * 共 633 個字；點陣資料放在 res.pak 的 0x63000 之後。
 */

#include "../lv_misc/lv_font.h"
#include <memory_map.h>

/* 字元表已依編碼排序，用二分搜尋找字，比內建的逐一比對快很多 */
static int _cjk_find(const lv_font_t *font, uint32_t letter)
{
    if (letter < font->unicode_first || letter > font->unicode_last)
        return -1;

    int lo = 0, hi = font->glyph_cnt - 1;
    while (lo <= hi)
    {
        int mid = (lo + hi) >> 1;
        uint32_t u = font->unicode_list[mid];
        if (u == letter)
            return mid;
        if (u < letter)
            lo = mid + 1;
        else
            hi = mid - 1;
    }

    return -1;
}

static const uint8_t *_cjk_get_bitmap(const lv_font_t *font, uint32_t letter)
{
    int i = _cjk_find(font, letter);
    return i < 0 ? NULL : &font->glyph_bitmap[font->glyph_dsc[i].glyph_index];
}

static int16_t _cjk_get_width(const lv_font_t *font, uint32_t letter)
{
    int i = _cjk_find(font, letter);
    return i < 0 ? -1 : font->glyph_dsc[i].w_px;
}

static const uint32_t cjk_tw_20_unicode[] = {
    0x2026, 0x3001, 0x3002, 0x300C, 0x300D, 0x4E00, 0x4E01, 0x4E03, 0x4E09, 0x4E0A, 0x4E0B, 0x4E0D,
    0x4E14, 0x4E19, 0x4E26, 0x4E2D, 0x4E3B, 0x4E45, 0x4E4B, 0x4E59, 0x4E5D, 0x4E5F, 0x4E86, 0x4E8C,
    0x4E94, 0x4E9B, 0x4EAE, 0x4EBA, 0x4ECA, 0x4ED6, 0x4EE3, 0x4EE4, 0x4EE5, 0x4EF6, 0x4EFB, 0x4EFD,
    0x4F0D, 0x4F30, 0x4F46, 0x4F4D, 0x4F4E, 0x4F55, 0x4F5C, 0x4F60, 0x4F75, 0x4F7F, 0x4F86, 0x4F9B,
    0x4FDD, 0x4FEE, 0x500B, 0x500D, 0x5011, 0x5012, 0x5019, 0x503C, 0x5047, 0x504F, 0x505A, 0x505C,
    0x5075, 0x5099, 0x50B3, 0x50CF, 0x5132, 0x5141, 0x5143, 0x5145, 0x5148, 0x5149, 0x514D, 0x5165,
    0x5167, 0x5168, 0x5169, 0x516B, 0x516C, 0x516D, 0x5171, 0x5176, 0x5177, 0x518D, 0x51AC, 0x51B7,
    0x51FA, 0x5206, 0x5207, 0x5217, 0x521D, 0x5225, 0x5229, 0x522A, 0x5230, 0x5236, 0x5237, 0x523B,
    0x5247, 0x524D, 0x526F, 0x5272, 0x529B, 0x529F, 0x52A0, 0x52A9, 0x52D5, 0x52D9, 0x5305, 0x5316,
    0x5317, 0x532F, 0x5340, 0x5341, 0x5343, 0x5348, 0x534A, 0x5353, 0x5357, 0x5361, 0x5371, 0x5373,
    0x5378, 0x539F, 0x53BB, 0x53C3, 0x53CA, 0x53D6, 0x53D7, 0x53E2, 0x53EA, 0x53EF, 0x53F0, 0x53F3,
    0x5404, 0x5408, 0x540C, 0x540D, 0x5426, 0x542B, 0x544A, 0x547D, 0x548C, 0x54C1, 0x552F, 0x5546,
    0x554F, 0x555F, 0x559A, 0x55AE, 0x55CE, 0x5617, 0x5668, 0x56B4, 0x56DB, 0x56DE, 0x56E0, 0x570D,
    0x5713, 0x5716, 0x5728, 0x5730, 0x5740, 0x5747, 0x578B, 0x57DF, 0x57F7, 0x57FA, 0x5831, 0x584A,
    0x58D3, 0x58DE, 0x58EC, 0x58F9, 0x58FD, 0x590F, 0x5916, 0x591A, 0x5927, 0x5929, 0x592A, 0x5931,
    0x593E, 0x5957, 0x5979, 0x597D, 0x5982, 0x59CB, 0x5B57, 0x5B58, 0x5B83, 0x5B89, 0x5B8C, 0x5B9A,
    0x5BB9, 0x5BC6, 0x5BE6, 0x5BEB, 0x5BEC, 0x5C01, 0x5C07, 0x5C0B, 0x5C0D, 0x5C0F, 0x5C11, 0x5C31,
    0x5C64, 0x5C6C, 0x5DE5, 0x5DE6, 0x5DF1, 0x5DF2, 0x5E33, 0x5E36, 0x5E38, 0x5E55, 0x5E6B, 0x5E73,
    0x5E74, 0x5E9A, 0x5EA6, 0x5EA7, 0x5EE0, 0x5EFA, 0x5F0F, 0x5F37, 0x5F62, 0x5F69, 0x5F71, 0x5F85,
    0x5F88, 0x5F8C, 0x5F91, 0x5F97, 0x5F9E, 0x5FA9, 0x5FC3, 0x5FC5, 0x5FEB, 0x6027, 0x6062, 0x606F,
    0x60F3, 0x610F, 0x611F, 0x614B, 0x6162, 0x61B6, 0x61C9, 0x620A, 0x6210, 0x6211, 0x6216, 0x622A,
    0x6232, 0x6240, 0x6247, 0x624B, 0x624D, 0x627E, 0x628A, 0x62BD, 0x62C6, 0x62D2, 0x62D4, 0x62FE,
    0x62FF, 0x6307, 0x6309, 0x634C, 0x6383, 0x6389, 0x6392, 0x639B, 0x63A2, 0x63A5, 0x63A7, 0x63CF,
    0x63D0, 0x63D2, 0x63DB, 0x63F4, 0x640D, 0x641C, 0x642C, 0x642D, 0x64C7, 0x64CD, 0x64EC, 0x64F4,
    0x652F, 0x6536, 0x6539, 0x653E, 0x6548, 0x6557, 0x6574, 0x6578, 0x6587, 0x6599, 0x65B0, 0x65B7,
    0x65B9, 0x65BC, 0x65E5, 0x65E9, 0x660E, 0x661F, 0x6620, 0x6625, 0x6628, 0x662F, 0x6642, 0x665A,
    0x666F, 0x6676, 0x6697, 0x66AB, 0x66F4, 0x66FF, 0x6700, 0x6703, 0x6708, 0x6709, 0x670D, 0x671F,
    0x672A, 0x672C, 0x675F, 0x6771, 0x677F, 0x6790, 0x679C, 0x67D2, 0x67E5, 0x6821, 0x6838, 0x6839,
    0x683C, 0x6848, 0x684C, 0x696D, 0x69FD, 0x6A19, 0x6A21, 0x6A23, 0x6A5F, 0x6A94, 0x6AA2, 0x6B0A,
    0x6B21, 0x6B61, 0x6B62, 0x6B63, 0x6B65, 0x6BB5, 0x6BC0, 0x6BCF, 0x6BD4, 0x6C23, 0x6C38, 0x6C42,
    0x6C60, 0x6C92, 0x6CD5, 0x6CE8, 0x6D1E, 0x6D41, 0x6D88, 0x6DF7, 0x6E05, 0x6E2C, 0x6E4A, 0x6E90,
    0x6E96, 0x6EAB, 0x6EFF, 0x6F0F, 0x7070, 0x70BA, 0x7121, 0x7194, 0x71B1, 0x71D2, 0x7247, 0x7248,
    0x7259, 0x7279, 0x72C0, 0x7368, 0x7387, 0x7396, 0x73FE, 0x7406, 0x751A, 0x751F, 0x7522, 0x7528,
    0x7532, 0x7559, 0x756B, 0x7570, 0x7576, 0x7678, 0x767B, 0x767C, 0x767D, 0x767E, 0x7684, 0x7686,
    0x76EE, 0x76F4, 0x76F8, 0x770B, 0x771F, 0x77E5, 0x77ED, 0x7834, 0x786C, 0x789F, 0x78B0, 0x78BA,
    0x78BC, 0x78C1, 0x790E, 0x793A, 0x7981, 0x79CB, 0x79D2, 0x79FB, 0x7A0B, 0x7A0D, 0x7A2E, 0x7A31,
    0x7A7A, 0x7ACB, 0x7B26, 0x7B2C, 0x7B49, 0x7B97, 0x7BA1, 0x7BC0, 0x7BC4, 0x7C21, 0x7C3F, 0x7CFB,
    0x7D00, 0x7D04, 0x7D1A, 0x7D30, 0x7D42, 0x7D44, 0x7D50, 0x7D55, 0x7D71, 0x7D72, 0x7D93, 0x7DAD,
    0x7DB2, 0x7DDA, 0x7E3D, 0x7E41, 0x7E7C, 0x7E8C, 0x7F3A, 0x7F6E, 0x8005, 0x800C, 0x8017, 0x8072,
    0x807D, 0x8086, 0x80CC, 0x80FD, 0x8166, 0x81EA, 0x81F3, 0x81F4, 0x8207, 0x820A, 0x822C, 0x826F,
    0x8272, 0x82F1, 0x842C, 0x85CD, 0x8655, 0x865B, 0x865F, 0x87A2, 0x884C, 0x8868, 0x88AB, 0x88DC,
    0x88DD, 0x88E1, 0x88FD, 0x8907, 0x897F, 0x8981, 0x898B, 0x898F, 0x89BD, 0x89C0, 0x89E3, 0x89F8,
    0x8A00, 0x8A02, 0x8A08, 0x8A0A, 0x8A18, 0x8A2D, 0x8A31, 0x8A3B, 0x8A62, 0x8A66, 0x8A71, 0x8A73,
    0x8A8C, 0x8A8D, 0x8A9E, 0x8AA4, 0x8AAA, 0x8ABF, 0x8ACB, 0x8B1D, 0x8B49, 0x8B66, 0x8B70, 0x8B77,
    0x8B80, 0x8B8A, 0x8B93, 0x8CB3, 0x8CBB, 0x8CC7, 0x8D70, 0x8D77, 0x8D85, 0x8DB3, 0x8DEF, 0x8DF3,
    0x8EDF, 0x8F03, 0x8F09, 0x8F15, 0x8F38, 0x8F49, 0x8F9B, 0x8FCE, 0x8FD4, 0x9000, 0x9001, 0x9010,
    0x9014, 0x9019, 0x901A, 0x901F, 0x9020, 0x9023, 0x9031, 0x9032, 0x904A, 0x904B, 0x904E, 0x9053,
    0x9069, 0x9078, 0x9084, 0x908A, 0x90E8, 0x90FD, 0x914D, 0x9192, 0x91CD, 0x91CF, 0x91D1, 0x9215,
    0x9304, 0x932F, 0x9375, 0x9396, 0x9418, 0x9470, 0x9577, 0x9589, 0x958B, 0x9593, 0x95DC, 0x964D,
    0x9650, 0x9664, 0x9678, 0x968E, 0x969B, 0x96AA, 0x96C6, 0x96DC, 0x96F6, 0x96FB, 0x9700, 0x975E,
    0x9762, 0x97CC, 0x97D3, 0x97F3, 0x97FF, 0x9801, 0x9805, 0x9808, 0x9810, 0x984C, 0x984F, 0x985E,
    0x986F, 0x98A8, 0x9996, 0x9A30, 0x9A57, 0x9AD4, 0x9AD8, 0x9EC3, 0x9ED1, 0x9EDE, 0x9F4A, 0xFF01,
    0xFF08, 0xFF09, 0xFF0C, 0xFF0F, 0xFF1A, 0xFF1B, 0xFF1F, 0xFF3B, 0xFF3D,
};
static const lv_font_glyph_dsc_t cjk_tw_20_dsc[] = {
    {.w_px = 17, .glyph_index = 0}, /* U+2026 … */
    {.w_px = 17, .glyph_index = 340}, /* U+3001 、 */
    {.w_px = 17, .glyph_index = 680}, /* U+3002 。 */
    {.w_px = 17, .glyph_index = 1020}, /* U+300C 「 */
    {.w_px = 17, .glyph_index = 1360}, /* U+300D 」 */
    {.w_px = 17, .glyph_index = 1700}, /* U+4E00 一 */
    {.w_px = 17, .glyph_index = 2040}, /* U+4E01 丁 */
    {.w_px = 17, .glyph_index = 2380}, /* U+4E03 七 */
    {.w_px = 17, .glyph_index = 2720}, /* U+4E09 三 */
    {.w_px = 17, .glyph_index = 3060}, /* U+4E0A 上 */
    {.w_px = 17, .glyph_index = 3400}, /* U+4E0B 下 */
    {.w_px = 17, .glyph_index = 3740}, /* U+4E0D 不 */
    {.w_px = 17, .glyph_index = 4080}, /* U+4E14 且 */
    {.w_px = 17, .glyph_index = 4420}, /* U+4E19 丙 */
    {.w_px = 17, .glyph_index = 4760}, /* U+4E26 並 */
    {.w_px = 17, .glyph_index = 5100}, /* U+4E2D 中 */
    {.w_px = 17, .glyph_index = 5440}, /* U+4E3B 主 */
    {.w_px = 17, .glyph_index = 5780}, /* U+4E45 久 */
    {.w_px = 17, .glyph_index = 6120}, /* U+4E4B 之 */
    {.w_px = 17, .glyph_index = 6460}, /* U+4E59 乙 */
    {.w_px = 17, .glyph_index = 6800}, /* U+4E5D 九 */
    {.w_px = 17, .glyph_index = 7140}, /* U+4E5F 也 */
    {.w_px = 17, .glyph_index = 7480}, /* U+4E86 了 */
    {.w_px = 17, .glyph_index = 7820}, /* U+4E8C 二 */
    {.w_px = 17, .glyph_index = 8160}, /* U+4E94 五 */
    {.w_px = 17, .glyph_index = 8500}, /* U+4E9B 些 */
    {.w_px = 17, .glyph_index = 8840}, /* U+4EAE 亮 */
    {.w_px = 17, .glyph_index = 9180}, /* U+4EBA 人 */
    {.w_px = 17, .glyph_index = 9520}, /* U+4ECA 今 */
    {.w_px = 17, .glyph_index = 9860}, /* U+4ED6 他 */
    {.w_px = 17, .glyph_index = 10200}, /* U+4EE3 代 */
    {.w_px = 17, .glyph_index = 10540}, /* U+4EE4 令 */
    {.w_px = 17, .glyph_index = 10880}, /* U+4EE5 以 */
    {.w_px = 17, .glyph_index = 11220}, /* U+4EF6 件 */
    {.w_px = 17, .glyph_index = 11560}, /* U+4EFB 任 */
    {.w_px = 17, .glyph_index = 11900}, /* U+4EFD 份 */
    {.w_px = 17, .glyph_index = 12240}, /* U+4F0D 伍 */
    {.w_px = 17, .glyph_index = 12580}, /* U+4F30 估 */
    {.w_px = 17, .glyph_index = 12920}, /* U+4F46 但 */
    {.w_px = 17, .glyph_index = 13260}, /* U+4F4D 位 */
    {.w_px = 17, .glyph_index = 13600}, /* U+4F4E 低 */
    {.w_px = 17, .glyph_index = 13940}, /* U+4F55 何 */
    {.w_px = 17, .glyph_index = 14280}, /* U+4F5C 作 */
    {.w_px = 17, .glyph_index = 14620}, /* U+4F60 你 */
    {.w_px = 17, .glyph_index = 14960}, /* U+4F75 併 */
    {.w_px = 17, .glyph_index = 15300}, /* U+4F7F 使 */
    {.w_px = 17, .glyph_index = 15640}, /* U+4F86 來 */
    {.w_px = 17, .glyph_index = 15980}, /* U+4F9B 供 */
    {.w_px = 17, .glyph_index = 16320}, /* U+4FDD 保 */
    {.w_px = 17, .glyph_index = 16660}, /* U+4FEE 修 */
    {.w_px = 17, .glyph_index = 17000}, /* U+500B 個 */
    {.w_px = 17, .glyph_index = 17340}, /* U+500D 倍 */
    {.w_px = 17, .glyph_index = 17680}, /* U+5011 們 */
    {.w_px = 17, .glyph_index = 18020}, /* U+5012 倒 */
    {.w_px = 17, .glyph_index = 18360}, /* U+5019 候 */
    {.w_px = 17, .glyph_index = 18700}, /* U+503C 值 */
    {.w_px = 17, .glyph_index = 19040}, /* U+5047 假 */
    {.w_px = 17, .glyph_index = 19380}, /* U+504F 偏 */
    {.w_px = 17, .glyph_index = 19720}, /* U+505A 做 */
    {.w_px = 17, .glyph_index = 20060}, /* U+505C 停 */
    {.w_px = 17, .glyph_index = 20400}, /* U+5075 偵 */
    {.w_px = 17, .glyph_index = 20740}, /* U+5099 備 */
    {.w_px = 17, .glyph_index = 21080}, /* U+50B3 傳 */
    {.w_px = 17, .glyph_index = 21420}, /* U+50CF 像 */
    {.w_px = 17, .glyph_index = 21760}, /* U+5132 儲 */
    {.w_px = 17, .glyph_index = 22100}, /* U+5141 允 */
    {.w_px = 17, .glyph_index = 22440}, /* U+5143 元 */
    {.w_px = 17, .glyph_index = 22780}, /* U+5145 充 */
    {.w_px = 17, .glyph_index = 23120}, /* U+5148 先 */
    {.w_px = 17, .glyph_index = 23460}, /* U+5149 光 */
    {.w_px = 17, .glyph_index = 23800}, /* U+514D 免 */
    {.w_px = 17, .glyph_index = 24140}, /* U+5165 入 */
    {.w_px = 17, .glyph_index = 24480}, /* U+5167 內 */
    {.w_px = 17, .glyph_index = 24820}, /* U+5168 全 */
    {.w_px = 17, .glyph_index = 25160}, /* U+5169 兩 */
    {.w_px = 17, .glyph_index = 25500}, /* U+516B 八 */
    {.w_px = 17, .glyph_index = 25840}, /* U+516C 公 */
    {.w_px = 17, .glyph_index = 26180}, /* U+516D 六 */
    {.w_px = 17, .glyph_index = 26520}, /* U+5171 共 */
    {.w_px = 17, .glyph_index = 26860}, /* U+5176 其 */
    {.w_px = 17, .glyph_index = 27200}, /* U+5177 具 */
    {.w_px = 17, .glyph_index = 27540}, /* U+518D 再 */
    {.w_px = 17, .glyph_index = 27880}, /* U+51AC 冬 */
    {.w_px = 17, .glyph_index = 28220}, /* U+51B7 冷 */
    {.w_px = 17, .glyph_index = 28560}, /* U+51FA 出 */
    {.w_px = 17, .glyph_index = 28900}, /* U+5206 分 */
    {.w_px = 17, .glyph_index = 29240}, /* U+5207 切 */
    {.w_px = 17, .glyph_index = 29580}, /* U+5217 列 */
    {.w_px = 17, .glyph_index = 29920}, /* U+521D 初 */
    {.w_px = 17, .glyph_index = 30260}, /* U+5225 別 */
    {.w_px = 17, .glyph_index = 30600}, /* U+5229 利 */
    {.w_px = 17, .glyph_index = 30940}, /* U+522A 刪 */
    {.w_px = 17, .glyph_index = 31280}, /* U+5230 到 */
    {.w_px = 17, .glyph_index = 31620}, /* U+5236 制 */
    {.w_px = 17, .glyph_index = 31960}, /* U+5237 刷 */
    {.w_px = 17, .glyph_index = 32300}, /* U+523B 刻 */
    {.w_px = 17, .glyph_index = 32640}, /* U+5247 則 */
    {.w_px = 17, .glyph_index = 32980}, /* U+524D 前 */
    {.w_px = 17, .glyph_index = 33320}, /* U+526F 副 */
    {.w_px = 17, .glyph_index = 33660}, /* U+5272 割 */
    {.w_px = 17, .glyph_index = 34000}, /* U+529B 力 */
    {.w_px = 17, .glyph_index = 34340}, /* U+529F 功 */
    {.w_px = 17, .glyph_index = 34680}, /* U+52A0 加 */
    {.w_px = 17, .glyph_index = 35020}, /* U+52A9 助 */
    {.w_px = 17, .glyph_index = 35360}, /* U+52D5 動 */
    {.w_px = 17, .glyph_index = 35700}, /* U+52D9 務 */
    {.w_px = 17, .glyph_index = 36040}, /* U+5305 包 */
    {.w_px = 17, .glyph_index = 36380}, /* U+5316 化 */
    {.w_px = 17, .glyph_index = 36720}, /* U+5317 北 */
    {.w_px = 17, .glyph_index = 37060}, /* U+532F 匯 */
    {.w_px = 17, .glyph_index = 37400}, /* U+5340 區 */
    {.w_px = 17, .glyph_index = 37740}, /* U+5341 十 */
    {.w_px = 17, .glyph_index = 38080}, /* U+5343 千 */
    {.w_px = 17, .glyph_index = 38420}, /* U+5348 午 */
    {.w_px = 17, .glyph_index = 38760}, /* U+534A 半 */
    {.w_px = 17, .glyph_index = 39100}, /* U+5353 卓 */
    {.w_px = 17, .glyph_index = 39440}, /* U+5357 南 */
    {.w_px = 17, .glyph_index = 39780}, /* U+5361 卡 */
    {.w_px = 17, .glyph_index = 40120}, /* U+5371 危 */
    {.w_px = 17, .glyph_index = 40460}, /* U+5373 即 */
    {.w_px = 17, .glyph_index = 40800}, /* U+5378 卸 */
    {.w_px = 17, .glyph_index = 41140}, /* U+539F 原 */
    {.w_px = 17, .glyph_index = 41480}, /* U+53BB 去 */
    {.w_px = 17, .glyph_index = 41820}, /* U+53C3 參 */
    {.w_px = 17, .glyph_index = 42160}, /* U+53CA 及 */
    {.w_px = 17, .glyph_index = 42500}, /* U+53D6 取 */
    {.w_px = 17, .glyph_index = 42840}, /* U+53D7 受 */
    {.w_px = 17, .glyph_index = 43180}, /* U+53E2 叢 */
    {.w_px = 17, .glyph_index = 43520}, /* U+53EA 只 */
    {.w_px = 17, .glyph_index = 43860}, /* U+53EF 可 */
    {.w_px = 17, .glyph_index = 44200}, /* U+53F0 台 */
    {.w_px = 17, .glyph_index = 44540}, /* U+53F3 右 */
    {.w_px = 17, .glyph_index = 44880}, /* U+5404 各 */
    {.w_px = 17, .glyph_index = 45220}, /* U+5408 合 */
    {.w_px = 17, .glyph_index = 45560}, /* U+540C 同 */
    {.w_px = 17, .glyph_index = 45900}, /* U+540D 名 */
    {.w_px = 17, .glyph_index = 46240}, /* U+5426 否 */
    {.w_px = 17, .glyph_index = 46580}, /* U+542B 含 */
    {.w_px = 17, .glyph_index = 46920}, /* U+544A 告 */
    {.w_px = 17, .glyph_index = 47260}, /* U+547D 命 */
    {.w_px = 17, .glyph_index = 47600}, /* U+548C 和 */
    {.w_px = 17, .glyph_index = 47940}, /* U+54C1 品 */
    {.w_px = 17, .glyph_index = 48280}, /* U+552F 唯 */
    {.w_px = 17, .glyph_index = 48620}, /* U+5546 商 */
    {.w_px = 17, .glyph_index = 48960}, /* U+554F 問 */
    {.w_px = 17, .glyph_index = 49300}, /* U+555F 啟 */
    {.w_px = 17, .glyph_index = 49640}, /* U+559A 喚 */
    {.w_px = 17, .glyph_index = 49980}, /* U+55AE 單 */
    {.w_px = 17, .glyph_index = 50320}, /* U+55CE 嗎 */
    {.w_px = 17, .glyph_index = 50660}, /* U+5617 嘗 */
    {.w_px = 17, .glyph_index = 51000}, /* U+5668 器 */
    {.w_px = 17, .glyph_index = 51340}, /* U+56B4 嚴 */
    {.w_px = 17, .glyph_index = 51680}, /* U+56DB 四 */
    {.w_px = 17, .glyph_index = 52020}, /* U+56DE 回 */
    {.w_px = 17, .glyph_index = 52360}, /* U+56E0 因 */
    {.w_px = 17, .glyph_index = 52700}, /* U+570D 圍 */
    {.w_px = 17, .glyph_index = 53040}, /* U+5713 圓 */
    {.w_px = 17, .glyph_index = 53380}, /* U+5716 圖 */
    {.w_px = 17, .glyph_index = 53720}, /* U+5728 在 */
    {.w_px = 17, .glyph_index = 54060}, /* U+5730 地 */
    {.w_px = 17, .glyph_index = 54400}, /* U+5740 址 */
    {.w_px = 17, .glyph_index = 54740}, /* U+5747 均 */
    {.w_px = 17, .glyph_index = 55080}, /* U+578B 型 */
    {.w_px = 17, .glyph_index = 55420}, /* U+57DF 域 */
    {.w_px = 17, .glyph_index = 55760}, /* U+57F7 執 */
    {.w_px = 17, .glyph_index = 56100}, /* U+57FA 基 */
    {.w_px = 17, .glyph_index = 56440}, /* U+5831 報 */
    {.w_px = 17, .glyph_index = 56780}, /* U+584A 塊 */
    {.w_px = 17, .glyph_index = 57120}, /* U+58D3 壓 */
    {.w_px = 17, .glyph_index = 57460}, /* U+58DE 壞 */
    {.w_px = 17, .glyph_index = 57800}, /* U+58EC 壬 */
    {.w_px = 17, .glyph_index = 58140}, /* U+58F9 壹 */
    {.w_px = 17, .glyph_index = 58480}, /* U+58FD 壽 */
    {.w_px = 17, .glyph_index = 58820}, /* U+590F 夏 */
    {.w_px = 17, .glyph_index = 59160}, /* U+5916 外 */
    {.w_px = 17, .glyph_index = 59500}, /* U+591A 多 */
    {.w_px = 17, .glyph_index = 59840}, /* U+5927 大 */
    {.w_px = 17, .glyph_index = 60180}, /* U+5929 天 */
    {.w_px = 17, .glyph_index = 60520}, /* U+592A 太 */
    {.w_px = 17, .glyph_index = 60860}, /* U+5931 失 */
    {.w_px = 17, .glyph_index = 61200}, /* U+593E 夾 */
    {.w_px = 17, .glyph_index = 61540}, /* U+5957 套 */
    {.w_px = 17, .glyph_index = 61880}, /* U+5979 她 */
    {.w_px = 17, .glyph_index = 62220}, /* U+597D 好 */
    {.w_px = 17, .glyph_index = 62560}, /* U+5982 如 */
    {.w_px = 17, .glyph_index = 62900}, /* U+59CB 始 */
    {.w_px = 17, .glyph_index = 63240}, /* U+5B57 字 */
    {.w_px = 17, .glyph_index = 63580}, /* U+5B58 存 */
    {.w_px = 17, .glyph_index = 63920}, /* U+5B83 它 */
    {.w_px = 17, .glyph_index = 64260}, /* U+5B89 安 */
    {.w_px = 17, .glyph_index = 64600}, /* U+5B8C 完 */
    {.w_px = 17, .glyph_index = 64940}, /* U+5B9A 定 */
    {.w_px = 17, .glyph_index = 65280}, /* U+5BB9 容 */
    {.w_px = 17, .glyph_index = 65620}, /* U+5BC6 密 */
    {.w_px = 17, .glyph_index = 65960}, /* U+5BE6 實 */
    {.w_px = 17, .glyph_index = 66300}, /* U+5BEB 寫 */
    {.w_px = 17, .glyph_index = 66640}, /* U+5BEC 寬 */
    {.w_px = 17, .glyph_index = 66980}, /* U+5C01 封 */
    {.w_px = 17, .glyph_index = 67320}, /* U+5C07 將 */
    {.w_px = 17, .glyph_index = 67660}, /* U+5C0B 尋 */
    {.w_px = 17, .glyph_index = 68000}, /* U+5C0D 對 */
    {.w_px = 17, .glyph_index = 68340}, /* U+5C0F 小 */
    {.w_px = 17, .glyph_index = 68680}, /* U+5C11 少 */
    {.w_px = 17, .glyph_index = 69020}, /* U+5C31 就 */
    {.w_px = 17, .glyph_index = 69360}, /* U+5C64 層 */
    {.w_px = 17, .glyph_index = 69700}, /* U+5C6C 屬 */
    {.w_px = 17, .glyph_index = 70040}, /* U+5DE5 工 */
    {.w_px = 17, .glyph_index = 70380}, /* U+5DE6 左 */
    {.w_px = 17, .glyph_index = 70720}, /* U+5DF1 己 */
    {.w_px = 17, .glyph_index = 71060}, /* U+5DF2 已 */
    {.w_px = 17, .glyph_index = 71400}, /* U+5E33 帳 */
    {.w_px = 17, .glyph_index = 71740}, /* U+5E36 帶 */
    {.w_px = 17, .glyph_index = 72080}, /* U+5E38 常 */
    {.w_px = 17, .glyph_index = 72420}, /* U+5E55 幕 */
    {.w_px = 17, .glyph_index = 72760}, /* U+5E6B 幫 */
    {.w_px = 17, .glyph_index = 73100}, /* U+5E73 平 */
    {.w_px = 17, .glyph_index = 73440}, /* U+5E74 年 */
    {.w_px = 17, .glyph_index = 73780}, /* U+5E9A 庚 */
    {.w_px = 17, .glyph_index = 74120}, /* U+5EA6 度 */
    {.w_px = 17, .glyph_index = 74460}, /* U+5EA7 座 */
    {.w_px = 17, .glyph_index = 74800}, /* U+5EE0 廠 */
    {.w_px = 17, .glyph_index = 75140}, /* U+5EFA 建 */
    {.w_px = 17, .glyph_index = 75480}, /* U+5F0F 式 */
    {.w_px = 17, .glyph_index = 75820}, /* U+5F37 強 */
    {.w_px = 17, .glyph_index = 76160}, /* U+5F62 形 */
    {.w_px = 17, .glyph_index = 76500}, /* U+5F69 彩 */
    {.w_px = 17, .glyph_index = 76840}, /* U+5F71 影 */
    {.w_px = 17, .glyph_index = 77180}, /* U+5F85 待 */
    {.w_px = 17, .glyph_index = 77520}, /* U+5F88 很 */
    {.w_px = 17, .glyph_index = 77860}, /* U+5F8C 後 */
    {.w_px = 17, .glyph_index = 78200}, /* U+5F91 徑 */
    {.w_px = 17, .glyph_index = 78540}, /* U+5F97 得 */
    {.w_px = 17, .glyph_index = 78880}, /* U+5F9E 從 */
    {.w_px = 17, .glyph_index = 79220}, /* U+5FA9 復 */
    {.w_px = 17, .glyph_index = 79560}, /* U+5FC3 心 */
    {.w_px = 17, .glyph_index = 79900}, /* U+5FC5 必 */
    {.w_px = 17, .glyph_index = 80240}, /* U+5FEB 快 */
    {.w_px = 17, .glyph_index = 80580}, /* U+6027 性 */
    {.w_px = 17, .glyph_index = 80920}, /* U+6062 恢 */
    {.w_px = 17, .glyph_index = 81260}, /* U+606F 息 */
    {.w_px = 17, .glyph_index = 81600}, /* U+60F3 想 */
    {.w_px = 17, .glyph_index = 81940}, /* U+610F 意 */
    {.w_px = 17, .glyph_index = 82280}, /* U+611F 感 */
    {.w_px = 17, .glyph_index = 82620}, /* U+614B 態 */
    {.w_px = 17, .glyph_index = 82960}, /* U+6162 慢 */
    {.w_px = 17, .glyph_index = 83300}, /* U+61B6 憶 */
    {.w_px = 17, .glyph_index = 83640}, /* U+61C9 應 */
    {.w_px = 17, .glyph_index = 83980}, /* U+620A 戊 */
    {.w_px = 17, .glyph_index = 84320}, /* U+6210 成 */
    {.w_px = 17, .glyph_index = 84660}, /* U+6211 我 */
    {.w_px = 17, .glyph_index = 85000}, /* U+6216 或 */
    {.w_px = 17, .glyph_index = 85340}, /* U+622A 截 */
    {.w_px = 17, .glyph_index = 85680}, /* U+6232 戲 */
    {.w_px = 17, .glyph_index = 86020}, /* U+6240 所 */
    {.w_px = 17, .glyph_index = 86360}, /* U+6247 扇 */
    {.w_px = 17, .glyph_index = 86700}, /* U+624B 手 */
    {.w_px = 17, .glyph_index = 87040}, /* U+624D 才 */
    {.w_px = 17, .glyph_index = 87380}, /* U+627E 找 */
    {.w_px = 17, .glyph_index = 87720}, /* U+628A 把 */
    {.w_px = 17, .glyph_index = 88060}, /* U+62BD 抽 */
    {.w_px = 17, .glyph_index = 88400}, /* U+62C6 拆 */
    {.w_px = 17, .glyph_index = 88740}, /* U+62D2 拒 */
    {.w_px = 17, .glyph_index = 89080}, /* U+62D4 拔 */
    {.w_px = 17, .glyph_index = 89420}, /* U+62FE 拾 */
    {.w_px = 17, .glyph_index = 89760}, /* U+62FF 拿 */
    {.w_px = 17, .glyph_index = 90100}, /* U+6307 指 */
    {.w_px = 17, .glyph_index = 90440}, /* U+6309 按 */
    {.w_px = 17, .glyph_index = 90780}, /* U+634C 捌 */
    {.w_px = 17, .glyph_index = 91120}, /* U+6383 掃 */
    {.w_px = 17, .glyph_index = 91460}, /* U+6389 掉 */
    {.w_px = 17, .glyph_index = 91800}, /* U+6392 排 */
    {.w_px = 17, .glyph_index = 92140}, /* U+639B 掛 */
    {.w_px = 17, .glyph_index = 92480}, /* U+63A2 探 */
    {.w_px = 17, .glyph_index = 92820}, /* U+63A5 接 */
    {.w_px = 17, .glyph_index = 93160}, /* U+63A7 控 */
    {.w_px = 17, .glyph_index = 93500}, /* U+63CF 描 */
    {.w_px = 17, .glyph_index = 93840}, /* U+63D0 提 */
    {.w_px = 17, .glyph_index = 94180}, /* U+63D2 插 */
    {.w_px = 17, .glyph_index = 94520}, /* U+63DB 換 */
    {.w_px = 17, .glyph_index = 94860}, /* U+63F4 援 */
    {.w_px = 17, .glyph_index = 95200}, /* U+640D 損 */
    {.w_px = 17, .glyph_index = 95540}, /* U+641C 搜 */
    {.w_px = 17, .glyph_index = 95880}, /* U+642C 搬 */
    {.w_px = 17, .glyph_index = 96220}, /* U+642D 搭 */
    {.w_px = 17, .glyph_index = 96560}, /* U+64C7 擇 */
    {.w_px = 17, .glyph_index = 96900}, /* U+64CD 操 */
    {.w_px = 17, .glyph_index = 97240}, /* U+64EC 擬 */
    {.w_px = 17, .glyph_index = 97580}, /* U+64F4 擴 */
    {.w_px = 17, .glyph_index = 97920}, /* U+652F 支 */
    {.w_px = 17, .glyph_index = 98260}, /* U+6536 收 */
    {.w_px = 17, .glyph_index = 98600}, /* U+6539 改 */
    {.w_px = 17, .glyph_index = 98940}, /* U+653E 放 */
    {.w_px = 17, .glyph_index = 99280}, /* U+6548 效 */
    {.w_px = 17, .glyph_index = 99620}, /* U+6557 敗 */
    {.w_px = 17, .glyph_index = 99960}, /* U+6574 整 */
    {.w_px = 17, .glyph_index = 100300}, /* U+6578 數 */
    {.w_px = 17, .glyph_index = 100640}, /* U+6587 文 */
    {.w_px = 17, .glyph_index = 100980}, /* U+6599 料 */
    {.w_px = 17, .glyph_index = 101320}, /* U+65B0 新 */
    {.w_px = 17, .glyph_index = 101660}, /* U+65B7 斷 */
    {.w_px = 17, .glyph_index = 102000}, /* U+65B9 方 */
    {.w_px = 17, .glyph_index = 102340}, /* U+65BC 於 */
    {.w_px = 17, .glyph_index = 102680}, /* U+65E5 日 */
    {.w_px = 17, .glyph_index = 103020}, /* U+65E9 早 */
    {.w_px = 17, .glyph_index = 103360}, /* U+660E 明 */
    {.w_px = 17, .glyph_index = 103700}, /* U+661F 星 */
    {.w_px = 17, .glyph_index = 104040}, /* U+6620 映 */
    {.w_px = 17, .glyph_index = 104380}, /* U+6625 春 */
    {.w_px = 17, .glyph_index = 104720}, /* U+6628 昨 */
    {.w_px = 17, .glyph_index = 105060}, /* U+662F 是 */
    {.w_px = 17, .glyph_index = 105400}, /* U+6642 時 */
    {.w_px = 17, .glyph_index = 105740}, /* U+665A 晚 */
    {.w_px = 17, .glyph_index = 106080}, /* U+666F 景 */
    {.w_px = 17, .glyph_index = 106420}, /* U+6676 晶 */
    {.w_px = 17, .glyph_index = 106760}, /* U+6697 暗 */
    {.w_px = 17, .glyph_index = 107100}, /* U+66AB 暫 */
    {.w_px = 17, .glyph_index = 107440}, /* U+66F4 更 */
    {.w_px = 17, .glyph_index = 107780}, /* U+66FF 替 */
    {.w_px = 17, .glyph_index = 108120}, /* U+6700 最 */
    {.w_px = 17, .glyph_index = 108460}, /* U+6703 會 */
    {.w_px = 17, .glyph_index = 108800}, /* U+6708 月 */
    {.w_px = 17, .glyph_index = 109140}, /* U+6709 有 */
    {.w_px = 17, .glyph_index = 109480}, /* U+670D 服 */
    {.w_px = 17, .glyph_index = 109820}, /* U+671F 期 */
    {.w_px = 17, .glyph_index = 110160}, /* U+672A 未 */
    {.w_px = 17, .glyph_index = 110500}, /* U+672C 本 */
    {.w_px = 17, .glyph_index = 110840}, /* U+675F 束 */
    {.w_px = 17, .glyph_index = 111180}, /* U+6771 東 */
    {.w_px = 17, .glyph_index = 111520}, /* U+677F 板 */
    {.w_px = 17, .glyph_index = 111860}, /* U+6790 析 */
    {.w_px = 17, .glyph_index = 112200}, /* U+679C 果 */
    {.w_px = 17, .glyph_index = 112540}, /* U+67D2 柒 */
    {.w_px = 17, .glyph_index = 112880}, /* U+67E5 查 */
    {.w_px = 17, .glyph_index = 113220}, /* U+6821 校 */
    {.w_px = 17, .glyph_index = 113560}, /* U+6838 核 */
    {.w_px = 17, .glyph_index = 113900}, /* U+6839 根 */
    {.w_px = 17, .glyph_index = 114240}, /* U+683C 格 */
    {.w_px = 17, .glyph_index = 114580}, /* U+6848 案 */
    {.w_px = 17, .glyph_index = 114920}, /* U+684C 桌 */
    {.w_px = 17, .glyph_index = 115260}, /* U+696D 業 */
    {.w_px = 17, .glyph_index = 115600}, /* U+69FD 槽 */
    {.w_px = 17, .glyph_index = 115940}, /* U+6A19 標 */
    {.w_px = 17, .glyph_index = 116280}, /* U+6A21 模 */
    {.w_px = 17, .glyph_index = 116620}, /* U+6A23 樣 */
    {.w_px = 17, .glyph_index = 116960}, /* U+6A5F 機 */
    {.w_px = 17, .glyph_index = 117300}, /* U+6A94 檔 */
    {.w_px = 17, .glyph_index = 117640}, /* U+6AA2 檢 */
    {.w_px = 17, .glyph_index = 117980}, /* U+6B0A 權 */
    {.w_px = 17, .glyph_index = 118320}, /* U+6B21 次 */
    {.w_px = 17, .glyph_index = 118660}, /* U+6B61 歡 */
    {.w_px = 17, .glyph_index = 119000}, /* U+6B62 止 */
    {.w_px = 17, .glyph_index = 119340}, /* U+6B63 正 */
    {.w_px = 17, .glyph_index = 119680}, /* U+6B65 步 */
    {.w_px = 17, .glyph_index = 120020}, /* U+6BB5 段 */
    {.w_px = 17, .glyph_index = 120360}, /* U+6BC0 毀 */
    {.w_px = 17, .glyph_index = 120700}, /* U+6BCF 每 */
    {.w_px = 17, .glyph_index = 121040}, /* U+6BD4 比 */
    {.w_px = 17, .glyph_index = 121380}, /* U+6C23 氣 */
    {.w_px = 17, .glyph_index = 121720}, /* U+6C38 永 */
    {.w_px = 17, .glyph_index = 122060}, /* U+6C42 求 */
    {.w_px = 17, .glyph_index = 122400}, /* U+6C60 池 */
    {.w_px = 17, .glyph_index = 122740}, /* U+6C92 沒 */
    {.w_px = 17, .glyph_index = 123080}, /* U+6CD5 法 */
    {.w_px = 17, .glyph_index = 123420}, /* U+6CE8 注 */
    {.w_px = 17, .glyph_index = 123760}, /* U+6D1E 洞 */
    {.w_px = 17, .glyph_index = 124100}, /* U+6D41 流 */
    {.w_px = 17, .glyph_index = 124440}, /* U+6D88 消 */
    {.w_px = 17, .glyph_index = 124780}, /* U+6DF7 混 */
    {.w_px = 17, .glyph_index = 125120}, /* U+6E05 清 */
    {.w_px = 17, .glyph_index = 125460}, /* U+6E2C 測 */
    {.w_px = 17, .glyph_index = 125800}, /* U+6E4A 湊 */
    {.w_px = 17, .glyph_index = 126140}, /* U+6E90 源 */
    {.w_px = 17, .glyph_index = 126480}, /* U+6E96 準 */
    {.w_px = 17, .glyph_index = 126820}, /* U+6EAB 溫 */
    {.w_px = 17, .glyph_index = 127160}, /* U+6EFF 滿 */
    {.w_px = 17, .glyph_index = 127500}, /* U+6F0F 漏 */
    {.w_px = 17, .glyph_index = 127840}, /* U+7070 灰 */
    {.w_px = 17, .glyph_index = 128180}, /* U+70BA 為 */
    {.w_px = 17, .glyph_index = 128520}, /* U+7121 無 */
    {.w_px = 17, .glyph_index = 128860}, /* U+7194 熔 */
    {.w_px = 17, .glyph_index = 129200}, /* U+71B1 熱 */
    {.w_px = 17, .glyph_index = 129540}, /* U+71D2 燒 */
    {.w_px = 17, .glyph_index = 129880}, /* U+7247 片 */
    {.w_px = 17, .glyph_index = 130220}, /* U+7248 版 */
    {.w_px = 17, .glyph_index = 130560}, /* U+7259 牙 */
    {.w_px = 17, .glyph_index = 130900}, /* U+7279 特 */
    {.w_px = 17, .glyph_index = 131240}, /* U+72C0 狀 */
    {.w_px = 17, .glyph_index = 131580}, /* U+7368 獨 */
    {.w_px = 17, .glyph_index = 131920}, /* U+7387 率 */
    {.w_px = 17, .glyph_index = 132260}, /* U+7396 玖 */
    {.w_px = 17, .glyph_index = 132600}, /* U+73FE 現 */
    {.w_px = 17, .glyph_index = 132940}, /* U+7406 理 */
    {.w_px = 17, .glyph_index = 133280}, /* U+751A 甚 */
    {.w_px = 17, .glyph_index = 133620}, /* U+751F 生 */
    {.w_px = 17, .glyph_index = 133960}, /* U+7522 產 */
    {.w_px = 17, .glyph_index = 134300}, /* U+7528 用 */
    {.w_px = 17, .glyph_index = 134640}, /* U+7532 甲 */
    {.w_px = 17, .glyph_index = 134980}, /* U+7559 留 */
    {.w_px = 17, .glyph_index = 135320}, /* U+756B 畫 */
    {.w_px = 17, .glyph_index = 135660}, /* U+7570 異 */
    {.w_px = 17, .glyph_index = 136000}, /* U+7576 當 */
    {.w_px = 17, .glyph_index = 136340}, /* U+7678 癸 */
    {.w_px = 17, .glyph_index = 136680}, /* U+767B 登 */
    {.w_px = 17, .glyph_index = 137020}, /* U+767C 發 */
    {.w_px = 17, .glyph_index = 137360}, /* U+767D 白 */
    {.w_px = 17, .glyph_index = 137700}, /* U+767E 百 */
    {.w_px = 17, .glyph_index = 138040}, /* U+7684 的 */
    {.w_px = 17, .glyph_index = 138380}, /* U+7686 皆 */
    {.w_px = 17, .glyph_index = 138720}, /* U+76EE 目 */
    {.w_px = 17, .glyph_index = 139060}, /* U+76F4 直 */
    {.w_px = 17, .glyph_index = 139400}, /* U+76F8 相 */
    {.w_px = 17, .glyph_index = 139740}, /* U+770B 看 */
    {.w_px = 17, .glyph_index = 140080}, /* U+771F 真 */
    {.w_px = 17, .glyph_index = 140420}, /* U+77E5 知 */
    {.w_px = 17, .glyph_index = 140760}, /* U+77ED 短 */
    {.w_px = 17, .glyph_index = 141100}, /* U+7834 破 */
    {.w_px = 17, .glyph_index = 141440}, /* U+786C 硬 */
    {.w_px = 17, .glyph_index = 141780}, /* U+789F 碟 */
    {.w_px = 17, .glyph_index = 142120}, /* U+78B0 碰 */
    {.w_px = 17, .glyph_index = 142460}, /* U+78BA 確 */
    {.w_px = 17, .glyph_index = 142800}, /* U+78BC 碼 */
    {.w_px = 17, .glyph_index = 143140}, /* U+78C1 磁 */
    {.w_px = 17, .glyph_index = 143480}, /* U+790E 礎 */
    {.w_px = 17, .glyph_index = 143820}, /* U+793A 示 */
    {.w_px = 17, .glyph_index = 144160}, /* U+7981 禁 */
    {.w_px = 17, .glyph_index = 144500}, /* U+79CB 秋 */
    {.w_px = 17, .glyph_index = 144840}, /* U+79D2 秒 */
    {.w_px = 17, .glyph_index = 145180}, /* U+79FB 移 */
    {.w_px = 17, .glyph_index = 145520}, /* U+7A0B 程 */
    {.w_px = 17, .glyph_index = 145860}, /* U+7A0D 稍 */
    {.w_px = 17, .glyph_index = 146200}, /* U+7A2E 種 */
    {.w_px = 17, .glyph_index = 146540}, /* U+7A31 稱 */
    {.w_px = 17, .glyph_index = 146880}, /* U+7A7A 空 */
    {.w_px = 17, .glyph_index = 147220}, /* U+7ACB 立 */
    {.w_px = 17, .glyph_index = 147560}, /* U+7B26 符 */
    {.w_px = 17, .glyph_index = 147900}, /* U+7B2C 第 */
    {.w_px = 17, .glyph_index = 148240}, /* U+7B49 等 */
    {.w_px = 17, .glyph_index = 148580}, /* U+7B97 算 */
    {.w_px = 17, .glyph_index = 148920}, /* U+7BA1 管 */
    {.w_px = 17, .glyph_index = 149260}, /* U+7BC0 節 */
    {.w_px = 17, .glyph_index = 149600}, /* U+7BC4 範 */
    {.w_px = 17, .glyph_index = 149940}, /* U+7C21 簡 */
    {.w_px = 17, .glyph_index = 150280}, /* U+7C3F 簿 */
    {.w_px = 17, .glyph_index = 150620}, /* U+7CFB 系 */
    {.w_px = 17, .glyph_index = 150960}, /* U+7D00 紀 */
    {.w_px = 17, .glyph_index = 151300}, /* U+7D04 約 */
    {.w_px = 17, .glyph_index = 151640}, /* U+7D1A 級 */
    {.w_px = 17, .glyph_index = 151980}, /* U+7D30 細 */
    {.w_px = 17, .glyph_index = 152320}, /* U+7D42 終 */
    {.w_px = 17, .glyph_index = 152660}, /* U+7D44 組 */
    {.w_px = 17, .glyph_index = 153000}, /* U+7D50 結 */
    {.w_px = 17, .glyph_index = 153340}, /* U+7D55 絕 */
    {.w_px = 17, .glyph_index = 153680}, /* U+7D71 統 */
    {.w_px = 17, .glyph_index = 154020}, /* U+7D72 絲 */
    {.w_px = 17, .glyph_index = 154360}, /* U+7D93 經 */
    {.w_px = 17, .glyph_index = 154700}, /* U+7DAD 維 */
    {.w_px = 17, .glyph_index = 155040}, /* U+7DB2 網 */
    {.w_px = 17, .glyph_index = 155380}, /* U+7DDA 線 */
    {.w_px = 17, .glyph_index = 155720}, /* U+7E3D 總 */
    {.w_px = 17, .glyph_index = 156060}, /* U+7E41 繁 */
    {.w_px = 17, .glyph_index = 156400}, /* U+7E7C 繼 */
    {.w_px = 17, .glyph_index = 156740}, /* U+7E8C 續 */
    {.w_px = 17, .glyph_index = 157080}, /* U+7F3A 缺 */
    {.w_px = 17, .glyph_index = 157420}, /* U+7F6E 置 */
    {.w_px = 17, .glyph_index = 157760}, /* U+8005 者 */
    {.w_px = 17, .glyph_index = 158100}, /* U+800C 而 */
    {.w_px = 17, .glyph_index = 158440}, /* U+8017 耗 */
    {.w_px = 17, .glyph_index = 158780}, /* U+8072 聲 */
    {.w_px = 17, .glyph_index = 159120}, /* U+807D 聽 */
    {.w_px = 17, .glyph_index = 159460}, /* U+8086 肆 */
    {.w_px = 17, .glyph_index = 159800}, /* U+80CC 背 */
    {.w_px = 17, .glyph_index = 160140}, /* U+80FD 能 */
    {.w_px = 17, .glyph_index = 160480}, /* U+8166 腦 */
    {.w_px = 17, .glyph_index = 160820}, /* U+81EA 自 */
    {.w_px = 17, .glyph_index = 161160}, /* U+81F3 至 */
    {.w_px = 17, .glyph_index = 161500}, /* U+81F4 致 */
    {.w_px = 17, .glyph_index = 161840}, /* U+8207 與 */
    {.w_px = 17, .glyph_index = 162180}, /* U+820A 舊 */
    {.w_px = 17, .glyph_index = 162520}, /* U+822C 般 */
    {.w_px = 17, .glyph_index = 162860}, /* U+826F 良 */
    {.w_px = 17, .glyph_index = 163200}, /* U+8272 色 */
    {.w_px = 17, .glyph_index = 163540}, /* U+82F1 英 */
    {.w_px = 17, .glyph_index = 163880}, /* U+842C 萬 */
    {.w_px = 17, .glyph_index = 164220}, /* U+85CD 藍 */
    {.w_px = 17, .glyph_index = 164560}, /* U+8655 處 */
    {.w_px = 17, .glyph_index = 164900}, /* U+865B 虛 */
    {.w_px = 17, .glyph_index = 165240}, /* U+865F 號 */
    {.w_px = 17, .glyph_index = 165580}, /* U+87A2 螢 */
    {.w_px = 17, .glyph_index = 165920}, /* U+884C 行 */
    {.w_px = 17, .glyph_index = 166260}, /* U+8868 表 */
    {.w_px = 17, .glyph_index = 166600}, /* U+88AB 被 */
    {.w_px = 17, .glyph_index = 166940}, /* U+88DC 補 */
    {.w_px = 17, .glyph_index = 167280}, /* U+88DD 裝 */
    {.w_px = 17, .glyph_index = 167620}, /* U+88E1 裡 */
    {.w_px = 17, .glyph_index = 167960}, /* U+88FD 製 */
    {.w_px = 17, .glyph_index = 168300}, /* U+8907 複 */
    {.w_px = 17, .glyph_index = 168640}, /* U+897F 西 */
    {.w_px = 17, .glyph_index = 168980}, /* U+8981 要 */
    {.w_px = 17, .glyph_index = 169320}, /* U+898B 見 */
    {.w_px = 17, .glyph_index = 169660}, /* U+898F 規 */
    {.w_px = 17, .glyph_index = 170000}, /* U+89BD 覽 */
    {.w_px = 17, .glyph_index = 170340}, /* U+89C0 觀 */
    {.w_px = 17, .glyph_index = 170680}, /* U+89E3 解 */
    {.w_px = 17, .glyph_index = 171020}, /* U+89F8 觸 */
    {.w_px = 17, .glyph_index = 171360}, /* U+8A00 言 */
    {.w_px = 17, .glyph_index = 171700}, /* U+8A02 訂 */
    {.w_px = 17, .glyph_index = 172040}, /* U+8A08 計 */
    {.w_px = 17, .glyph_index = 172380}, /* U+8A0A 訊 */
    {.w_px = 17, .glyph_index = 172720}, /* U+8A18 記 */
    {.w_px = 17, .glyph_index = 173060}, /* U+8A2D 設 */
    {.w_px = 17, .glyph_index = 173400}, /* U+8A31 許 */
    {.w_px = 17, .glyph_index = 173740}, /* U+8A3B 註 */
    {.w_px = 17, .glyph_index = 174080}, /* U+8A62 詢 */
    {.w_px = 17, .glyph_index = 174420}, /* U+8A66 試 */
    {.w_px = 17, .glyph_index = 174760}, /* U+8A71 話 */
    {.w_px = 17, .glyph_index = 175100}, /* U+8A73 詳 */
    {.w_px = 17, .glyph_index = 175440}, /* U+8A8C 誌 */
    {.w_px = 17, .glyph_index = 175780}, /* U+8A8D 認 */
    {.w_px = 17, .glyph_index = 176120}, /* U+8A9E 語 */
    {.w_px = 17, .glyph_index = 176460}, /* U+8AA4 誤 */
    {.w_px = 17, .glyph_index = 176800}, /* U+8AAA 說 */
    {.w_px = 17, .glyph_index = 177140}, /* U+8ABF 調 */
    {.w_px = 17, .glyph_index = 177480}, /* U+8ACB 請 */
    {.w_px = 17, .glyph_index = 177820}, /* U+8B1D 謝 */
    {.w_px = 17, .glyph_index = 178160}, /* U+8B49 證 */
    {.w_px = 17, .glyph_index = 178500}, /* U+8B66 警 */
    {.w_px = 17, .glyph_index = 178840}, /* U+8B70 議 */
    {.w_px = 17, .glyph_index = 179180}, /* U+8B77 護 */
    {.w_px = 17, .glyph_index = 179520}, /* U+8B80 讀 */
    {.w_px = 17, .glyph_index = 179860}, /* U+8B8A 變 */
    {.w_px = 17, .glyph_index = 180200}, /* U+8B93 讓 */
    {.w_px = 17, .glyph_index = 180540}, /* U+8CB3 貳 */
    {.w_px = 17, .glyph_index = 180880}, /* U+8CBB 費 */
    {.w_px = 17, .glyph_index = 181220}, /* U+8CC7 資 */
    {.w_px = 17, .glyph_index = 181560}, /* U+8D70 走 */
    {.w_px = 17, .glyph_index = 181900}, /* U+8D77 起 */
    {.w_px = 17, .glyph_index = 182240}, /* U+8D85 超 */
    {.w_px = 17, .glyph_index = 182580}, /* U+8DB3 足 */
    {.w_px = 17, .glyph_index = 182920}, /* U+8DEF 路 */
    {.w_px = 17, .glyph_index = 183260}, /* U+8DF3 跳 */
    {.w_px = 17, .glyph_index = 183600}, /* U+8EDF 軟 */
    {.w_px = 17, .glyph_index = 183940}, /* U+8F03 較 */
    {.w_px = 17, .glyph_index = 184280}, /* U+8F09 載 */
    {.w_px = 17, .glyph_index = 184620}, /* U+8F15 輕 */
    {.w_px = 17, .glyph_index = 184960}, /* U+8F38 輸 */
    {.w_px = 17, .glyph_index = 185300}, /* U+8F49 轉 */
    {.w_px = 17, .glyph_index = 185640}, /* U+8F9B 辛 */
    {.w_px = 17, .glyph_index = 185980}, /* U+8FCE 迎 */
    {.w_px = 17, .glyph_index = 186320}, /* U+8FD4 返 */
    {.w_px = 17, .glyph_index = 186660}, /* U+9000 退 */
    {.w_px = 17, .glyph_index = 187000}, /* U+9001 送 */
    {.w_px = 17, .glyph_index = 187340}, /* U+9010 逐 */
    {.w_px = 17, .glyph_index = 187680}, /* U+9014 途 */
    {.w_px = 17, .glyph_index = 188020}, /* U+9019 這 */
    {.w_px = 17, .glyph_index = 188360}, /* U+901A 通 */
    {.w_px = 17, .glyph_index = 188700}, /* U+901F 速 */
    {.w_px = 17, .glyph_index = 189040}, /* U+9020 造 */
    {.w_px = 17, .glyph_index = 189380}, /* U+9023 連 */
    {.w_px = 17, .glyph_index = 189720}, /* U+9031 週 */
    {.w_px = 17, .glyph_index = 190060}, /* U+9032 進 */
    {.w_px = 17, .glyph_index = 190400}, /* U+904A 遊 */
    {.w_px = 17, .glyph_index = 190740}, /* U+904B 運 */
    {.w_px = 17, .glyph_index = 191080}, /* U+904E 過 */
    {.w_px = 17, .glyph_index = 191420}, /* U+9053 道 */
    {.w_px = 17, .glyph_index = 191760}, /* U+9069 適 */
    {.w_px = 17, .glyph_index = 192100}, /* U+9078 選 */
    {.w_px = 17, .glyph_index = 192440}, /* U+9084 還 */
    {.w_px = 17, .glyph_index = 192780}, /* U+908A 邊 */
    {.w_px = 17, .glyph_index = 193120}, /* U+90E8 部 */
    {.w_px = 17, .glyph_index = 193460}, /* U+90FD 都 */
    {.w_px = 17, .glyph_index = 193800}, /* U+914D 配 */
    {.w_px = 17, .glyph_index = 194140}, /* U+9192 醒 */
    {.w_px = 17, .glyph_index = 194480}, /* U+91CD 重 */
    {.w_px = 17, .glyph_index = 194820}, /* U+91CF 量 */
    {.w_px = 17, .glyph_index = 195160}, /* U+91D1 金 */
    {.w_px = 17, .glyph_index = 195500}, /* U+9215 鈕 */
    {.w_px = 17, .glyph_index = 195840}, /* U+9304 錄 */
    {.w_px = 17, .glyph_index = 196180}, /* U+932F 錯 */
    {.w_px = 17, .glyph_index = 196520}, /* U+9375 鍵 */
    {.w_px = 17, .glyph_index = 196860}, /* U+9396 鎖 */
    {.w_px = 17, .glyph_index = 197200}, /* U+9418 鐘 */
    {.w_px = 17, .glyph_index = 197540}, /* U+9470 鑰 */
    {.w_px = 17, .glyph_index = 197880}, /* U+9577 長 */
    {.w_px = 17, .glyph_index = 198220}, /* U+9589 閉 */
    {.w_px = 17, .glyph_index = 198560}, /* U+958B 開 */
    {.w_px = 17, .glyph_index = 198900}, /* U+9593 間 */
    {.w_px = 17, .glyph_index = 199240}, /* U+95DC 關 */
    {.w_px = 17, .glyph_index = 199580}, /* U+964D 降 */
    {.w_px = 17, .glyph_index = 199920}, /* U+9650 限 */
    {.w_px = 17, .glyph_index = 200260}, /* U+9664 除 */
    {.w_px = 17, .glyph_index = 200600}, /* U+9678 陸 */
    {.w_px = 17, .glyph_index = 200940}, /* U+968E 階 */
    {.w_px = 17, .glyph_index = 201280}, /* U+969B 際 */
    {.w_px = 17, .glyph_index = 201620}, /* U+96AA 險 */
    {.w_px = 17, .glyph_index = 201960}, /* U+96C6 集 */
    {.w_px = 17, .glyph_index = 202300}, /* U+96DC 雜 */
    {.w_px = 17, .glyph_index = 202640}, /* U+96F6 零 */
    {.w_px = 17, .glyph_index = 202980}, /* U+96FB 電 */
    {.w_px = 17, .glyph_index = 203320}, /* U+9700 需 */
    {.w_px = 17, .glyph_index = 203660}, /* U+975E 非 */
    {.w_px = 17, .glyph_index = 204000}, /* U+9762 面 */
    {.w_px = 17, .glyph_index = 204340}, /* U+97CC 韌 */
    {.w_px = 17, .glyph_index = 204680}, /* U+97D3 韓 */
    {.w_px = 17, .glyph_index = 205020}, /* U+97F3 音 */
    {.w_px = 17, .glyph_index = 205360}, /* U+97FF 響 */
    {.w_px = 17, .glyph_index = 205700}, /* U+9801 頁 */
    {.w_px = 17, .glyph_index = 206040}, /* U+9805 項 */
    {.w_px = 17, .glyph_index = 206380}, /* U+9808 須 */
    {.w_px = 17, .glyph_index = 206720}, /* U+9810 預 */
    {.w_px = 17, .glyph_index = 207060}, /* U+984C 題 */
    {.w_px = 17, .glyph_index = 207400}, /* U+984F 顏 */
    {.w_px = 17, .glyph_index = 207740}, /* U+985E 類 */
    {.w_px = 17, .glyph_index = 208080}, /* U+986F 顯 */
    {.w_px = 17, .glyph_index = 208420}, /* U+98A8 風 */
    {.w_px = 17, .glyph_index = 208760}, /* U+9996 首 */
    {.w_px = 17, .glyph_index = 209100}, /* U+9A30 騰 */
    {.w_px = 17, .glyph_index = 209440}, /* U+9A57 驗 */
    {.w_px = 17, .glyph_index = 209780}, /* U+9AD4 體 */
    {.w_px = 17, .glyph_index = 210120}, /* U+9AD8 高 */
    {.w_px = 17, .glyph_index = 210460}, /* U+9EC3 黃 */
    {.w_px = 17, .glyph_index = 210800}, /* U+9ED1 黑 */
    {.w_px = 17, .glyph_index = 211140}, /* U+9EDE 點 */
    {.w_px = 17, .glyph_index = 211480}, /* U+9F4A 齊 */
    {.w_px = 17, .glyph_index = 211820}, /* U+FF01 ！ */
    {.w_px = 17, .glyph_index = 212160}, /* U+FF08 （ */
    {.w_px = 17, .glyph_index = 212500}, /* U+FF09 ） */
    {.w_px = 17, .glyph_index = 212840}, /* U+FF0C ， */
    {.w_px = 17, .glyph_index = 213180}, /* U+FF0F ／ */
    {.w_px = 17, .glyph_index = 213520}, /* U+FF1A ： */
    {.w_px = 17, .glyph_index = 213860}, /* U+FF1B ； */
    {.w_px = 17, .glyph_index = 214200}, /* U+FF1F ？ */
    {.w_px = 17, .glyph_index = 214540}, /* U+FF3B ［ */
    {.w_px = 17, .glyph_index = 214880}, /* U+FF3D ］ */
};
lv_font_t cjk_tw_20 =
{
    .unicode_first = 0x2026,
    .unicode_last = 0xFF3D,
    .h_px = 20,
    .glyph_bitmap = (const uint8_t *)(NYX_RES_ADDR + 0x63000),
    .glyph_dsc = cjk_tw_20_dsc,
    .glyph_cnt = 633,
    .unicode_list = cjk_tw_20_unicode,
    .get_bitmap = _cjk_get_bitmap,
    .get_width = _cjk_get_width,
    .bpp = 8,
    .monospace = 0,
    .next_page = NULL,
};

static const uint32_t cjk_tw_30_unicode[] = {
    0x2026, 0x3001, 0x3002, 0x300C, 0x300D, 0x4E00, 0x4E01, 0x4E03, 0x4E09, 0x4E0A, 0x4E0B, 0x4E0D,
    0x4E14, 0x4E19, 0x4E26, 0x4E2D, 0x4E3B, 0x4E45, 0x4E4B, 0x4E59, 0x4E5D, 0x4E5F, 0x4E86, 0x4E8C,
    0x4E94, 0x4E9B, 0x4EAE, 0x4EBA, 0x4ECA, 0x4ED6, 0x4EE3, 0x4EE4, 0x4EE5, 0x4EF6, 0x4EFB, 0x4EFD,
    0x4F0D, 0x4F30, 0x4F46, 0x4F4D, 0x4F4E, 0x4F55, 0x4F5C, 0x4F60, 0x4F75, 0x4F7F, 0x4F86, 0x4F9B,
    0x4FDD, 0x4FEE, 0x500B, 0x500D, 0x5011, 0x5012, 0x5019, 0x503C, 0x5047, 0x504F, 0x505A, 0x505C,
    0x5075, 0x5099, 0x50B3, 0x50CF, 0x5132, 0x5141, 0x5143, 0x5145, 0x5148, 0x5149, 0x514D, 0x5165,
    0x5167, 0x5168, 0x5169, 0x516B, 0x516C, 0x516D, 0x5171, 0x5176, 0x5177, 0x518D, 0x51AC, 0x51B7,
    0x51FA, 0x5206, 0x5207, 0x5217, 0x521D, 0x5225, 0x5229, 0x522A, 0x5230, 0x5236, 0x5237, 0x523B,
    0x5247, 0x524D, 0x526F, 0x5272, 0x529B, 0x529F, 0x52A0, 0x52A9, 0x52D5, 0x52D9, 0x5305, 0x5316,
    0x5317, 0x532F, 0x5340, 0x5341, 0x5343, 0x5348, 0x534A, 0x5353, 0x5357, 0x5361, 0x5371, 0x5373,
    0x5378, 0x539F, 0x53BB, 0x53C3, 0x53CA, 0x53D6, 0x53D7, 0x53E2, 0x53EA, 0x53EF, 0x53F0, 0x53F3,
    0x5404, 0x5408, 0x540C, 0x540D, 0x5426, 0x542B, 0x544A, 0x547D, 0x548C, 0x54C1, 0x552F, 0x5546,
    0x554F, 0x555F, 0x559A, 0x55AE, 0x55CE, 0x5617, 0x5668, 0x56B4, 0x56DB, 0x56DE, 0x56E0, 0x570D,
    0x5713, 0x5716, 0x5728, 0x5730, 0x5740, 0x5747, 0x578B, 0x57DF, 0x57F7, 0x57FA, 0x5831, 0x584A,
    0x58D3, 0x58DE, 0x58EC, 0x58F9, 0x58FD, 0x590F, 0x5916, 0x591A, 0x5927, 0x5929, 0x592A, 0x5931,
    0x593E, 0x5957, 0x5979, 0x597D, 0x5982, 0x59CB, 0x5B57, 0x5B58, 0x5B83, 0x5B89, 0x5B8C, 0x5B9A,
    0x5BB9, 0x5BC6, 0x5BE6, 0x5BEB, 0x5BEC, 0x5C01, 0x5C07, 0x5C0B, 0x5C0D, 0x5C0F, 0x5C11, 0x5C31,
    0x5C64, 0x5C6C, 0x5DE5, 0x5DE6, 0x5DF1, 0x5DF2, 0x5E33, 0x5E36, 0x5E38, 0x5E55, 0x5E6B, 0x5E73,
    0x5E74, 0x5E9A, 0x5EA6, 0x5EA7, 0x5EE0, 0x5EFA, 0x5F0F, 0x5F37, 0x5F62, 0x5F69, 0x5F71, 0x5F85,
    0x5F88, 0x5F8C, 0x5F91, 0x5F97, 0x5F9E, 0x5FA9, 0x5FC3, 0x5FC5, 0x5FEB, 0x6027, 0x6062, 0x606F,
    0x60F3, 0x610F, 0x611F, 0x614B, 0x6162, 0x61B6, 0x61C9, 0x620A, 0x6210, 0x6211, 0x6216, 0x622A,
    0x6232, 0x6240, 0x6247, 0x624B, 0x624D, 0x627E, 0x628A, 0x62BD, 0x62C6, 0x62D2, 0x62D4, 0x62FE,
    0x62FF, 0x6307, 0x6309, 0x634C, 0x6383, 0x6389, 0x6392, 0x639B, 0x63A2, 0x63A5, 0x63A7, 0x63CF,
    0x63D0, 0x63D2, 0x63DB, 0x63F4, 0x640D, 0x641C, 0x642C, 0x642D, 0x64C7, 0x64CD, 0x64EC, 0x64F4,
    0x652F, 0x6536, 0x6539, 0x653E, 0x6548, 0x6557, 0x6574, 0x6578, 0x6587, 0x6599, 0x65B0, 0x65B7,
    0x65B9, 0x65BC, 0x65E5, 0x65E9, 0x660E, 0x661F, 0x6620, 0x6625, 0x6628, 0x662F, 0x6642, 0x665A,
    0x666F, 0x6676, 0x6697, 0x66AB, 0x66F4, 0x66FF, 0x6700, 0x6703, 0x6708, 0x6709, 0x670D, 0x671F,
    0x672A, 0x672C, 0x675F, 0x6771, 0x677F, 0x6790, 0x679C, 0x67D2, 0x67E5, 0x6821, 0x6838, 0x6839,
    0x683C, 0x6848, 0x684C, 0x696D, 0x69FD, 0x6A19, 0x6A21, 0x6A23, 0x6A5F, 0x6A94, 0x6AA2, 0x6B0A,
    0x6B21, 0x6B61, 0x6B62, 0x6B63, 0x6B65, 0x6BB5, 0x6BC0, 0x6BCF, 0x6BD4, 0x6C23, 0x6C38, 0x6C42,
    0x6C60, 0x6C92, 0x6CD5, 0x6CE8, 0x6D1E, 0x6D41, 0x6D88, 0x6DF7, 0x6E05, 0x6E2C, 0x6E4A, 0x6E90,
    0x6E96, 0x6EAB, 0x6EFF, 0x6F0F, 0x7070, 0x70BA, 0x7121, 0x7194, 0x71B1, 0x71D2, 0x7247, 0x7248,
    0x7259, 0x7279, 0x72C0, 0x7368, 0x7387, 0x7396, 0x73FE, 0x7406, 0x751A, 0x751F, 0x7522, 0x7528,
    0x7532, 0x7559, 0x756B, 0x7570, 0x7576, 0x7678, 0x767B, 0x767C, 0x767D, 0x767E, 0x7684, 0x7686,
    0x76EE, 0x76F4, 0x76F8, 0x770B, 0x771F, 0x77E5, 0x77ED, 0x7834, 0x786C, 0x789F, 0x78B0, 0x78BA,
    0x78BC, 0x78C1, 0x790E, 0x793A, 0x7981, 0x79CB, 0x79D2, 0x79FB, 0x7A0B, 0x7A0D, 0x7A2E, 0x7A31,
    0x7A7A, 0x7ACB, 0x7B26, 0x7B2C, 0x7B49, 0x7B97, 0x7BA1, 0x7BC0, 0x7BC4, 0x7C21, 0x7C3F, 0x7CFB,
    0x7D00, 0x7D04, 0x7D1A, 0x7D30, 0x7D42, 0x7D44, 0x7D50, 0x7D55, 0x7D71, 0x7D72, 0x7D93, 0x7DAD,
    0x7DB2, 0x7DDA, 0x7E3D, 0x7E41, 0x7E7C, 0x7E8C, 0x7F3A, 0x7F6E, 0x8005, 0x800C, 0x8017, 0x8072,
    0x807D, 0x8086, 0x80CC, 0x80FD, 0x8166, 0x81EA, 0x81F3, 0x81F4, 0x8207, 0x820A, 0x822C, 0x826F,
    0x8272, 0x82F1, 0x842C, 0x85CD, 0x8655, 0x865B, 0x865F, 0x87A2, 0x884C, 0x8868, 0x88AB, 0x88DC,
    0x88DD, 0x88E1, 0x88FD, 0x8907, 0x897F, 0x8981, 0x898B, 0x898F, 0x89BD, 0x89C0, 0x89E3, 0x89F8,
    0x8A00, 0x8A02, 0x8A08, 0x8A0A, 0x8A18, 0x8A2D, 0x8A31, 0x8A3B, 0x8A62, 0x8A66, 0x8A71, 0x8A73,
    0x8A8C, 0x8A8D, 0x8A9E, 0x8AA4, 0x8AAA, 0x8ABF, 0x8ACB, 0x8B1D, 0x8B49, 0x8B66, 0x8B70, 0x8B77,
    0x8B80, 0x8B8A, 0x8B93, 0x8CB3, 0x8CBB, 0x8CC7, 0x8D70, 0x8D77, 0x8D85, 0x8DB3, 0x8DEF, 0x8DF3,
    0x8EDF, 0x8F03, 0x8F09, 0x8F15, 0x8F38, 0x8F49, 0x8F9B, 0x8FCE, 0x8FD4, 0x9000, 0x9001, 0x9010,
    0x9014, 0x9019, 0x901A, 0x901F, 0x9020, 0x9023, 0x9031, 0x9032, 0x904A, 0x904B, 0x904E, 0x9053,
    0x9069, 0x9078, 0x9084, 0x908A, 0x90E8, 0x90FD, 0x914D, 0x9192, 0x91CD, 0x91CF, 0x91D1, 0x9215,
    0x9304, 0x932F, 0x9375, 0x9396, 0x9418, 0x9470, 0x9577, 0x9589, 0x958B, 0x9593, 0x95DC, 0x964D,
    0x9650, 0x9664, 0x9678, 0x968E, 0x969B, 0x96AA, 0x96C6, 0x96DC, 0x96F6, 0x96FB, 0x9700, 0x975E,
    0x9762, 0x97CC, 0x97D3, 0x97F3, 0x97FF, 0x9801, 0x9805, 0x9808, 0x9810, 0x984C, 0x984F, 0x985E,
    0x986F, 0x98A8, 0x9996, 0x9A30, 0x9A57, 0x9AD4, 0x9AD8, 0x9EC3, 0x9ED1, 0x9EDE, 0x9F4A, 0xFF01,
    0xFF08, 0xFF09, 0xFF0C, 0xFF0F, 0xFF1A, 0xFF1B, 0xFF1F, 0xFF3B, 0xFF3D,
};
static const lv_font_glyph_dsc_t cjk_tw_30_dsc[] = {
    {.w_px = 25, .glyph_index = 0}, /* U+2026 … */
    {.w_px = 25, .glyph_index = 750}, /* U+3001 、 */
    {.w_px = 25, .glyph_index = 1500}, /* U+3002 。 */
    {.w_px = 25, .glyph_index = 2250}, /* U+300C 「 */
    {.w_px = 25, .glyph_index = 3000}, /* U+300D 」 */
    {.w_px = 25, .glyph_index = 3750}, /* U+4E00 一 */
    {.w_px = 25, .glyph_index = 4500}, /* U+4E01 丁 */
    {.w_px = 25, .glyph_index = 5250}, /* U+4E03 七 */
    {.w_px = 25, .glyph_index = 6000}, /* U+4E09 三 */
    {.w_px = 25, .glyph_index = 6750}, /* U+4E0A 上 */
    {.w_px = 25, .glyph_index = 7500}, /* U+4E0B 下 */
    {.w_px = 25, .glyph_index = 8250}, /* U+4E0D 不 */
    {.w_px = 25, .glyph_index = 9000}, /* U+4E14 且 */
    {.w_px = 25, .glyph_index = 9750}, /* U+4E19 丙 */
    {.w_px = 25, .glyph_index = 10500}, /* U+4E26 並 */
    {.w_px = 25, .glyph_index = 11250}, /* U+4E2D 中 */
    {.w_px = 25, .glyph_index = 12000}, /* U+4E3B 主 */
    {.w_px = 25, .glyph_index = 12750}, /* U+4E45 久 */
    {.w_px = 25, .glyph_index = 13500}, /* U+4E4B 之 */
    {.w_px = 25, .glyph_index = 14250}, /* U+4E59 乙 */
    {.w_px = 25, .glyph_index = 15000}, /* U+4E5D 九 */
    {.w_px = 25, .glyph_index = 15750}, /* U+4E5F 也 */
    {.w_px = 25, .glyph_index = 16500}, /* U+4E86 了 */
    {.w_px = 25, .glyph_index = 17250}, /* U+4E8C 二 */
    {.w_px = 25, .glyph_index = 18000}, /* U+4E94 五 */
    {.w_px = 25, .glyph_index = 18750}, /* U+4E9B 些 */
    {.w_px = 25, .glyph_index = 19500}, /* U+4EAE 亮 */
    {.w_px = 25, .glyph_index = 20250}, /* U+4EBA 人 */
    {.w_px = 25, .glyph_index = 21000}, /* U+4ECA 今 */
    {.w_px = 25, .glyph_index = 21750}, /* U+4ED6 他 */
    {.w_px = 25, .glyph_index = 22500}, /* U+4EE3 代 */
    {.w_px = 25, .glyph_index = 23250}, /* U+4EE4 令 */
    {.w_px = 25, .glyph_index = 24000}, /* U+4EE5 以 */
    {.w_px = 25, .glyph_index = 24750}, /* U+4EF6 件 */
    {.w_px = 25, .glyph_index = 25500}, /* U+4EFB 任 */
    {.w_px = 25, .glyph_index = 26250}, /* U+4EFD 份 */
    {.w_px = 25, .glyph_index = 27000}, /* U+4F0D 伍 */
    {.w_px = 25, .glyph_index = 27750}, /* U+4F30 估 */
    {.w_px = 25, .glyph_index = 28500}, /* U+4F46 但 */
    {.w_px = 25, .glyph_index = 29250}, /* U+4F4D 位 */
    {.w_px = 25, .glyph_index = 30000}, /* U+4F4E 低 */
    {.w_px = 25, .glyph_index = 30750}, /* U+4F55 何 */
    {.w_px = 25, .glyph_index = 31500}, /* U+4F5C 作 */
    {.w_px = 25, .glyph_index = 32250}, /* U+4F60 你 */
    {.w_px = 25, .glyph_index = 33000}, /* U+4F75 併 */
    {.w_px = 25, .glyph_index = 33750}, /* U+4F7F 使 */
    {.w_px = 25, .glyph_index = 34500}, /* U+4F86 來 */
    {.w_px = 25, .glyph_index = 35250}, /* U+4F9B 供 */
    {.w_px = 25, .glyph_index = 36000}, /* U+4FDD 保 */
    {.w_px = 25, .glyph_index = 36750}, /* U+4FEE 修 */
    {.w_px = 25, .glyph_index = 37500}, /* U+500B 個 */
    {.w_px = 25, .glyph_index = 38250}, /* U+500D 倍 */
    {.w_px = 25, .glyph_index = 39000}, /* U+5011 們 */
    {.w_px = 25, .glyph_index = 39750}, /* U+5012 倒 */
    {.w_px = 25, .glyph_index = 40500}, /* U+5019 候 */
    {.w_px = 25, .glyph_index = 41250}, /* U+503C 值 */
    {.w_px = 25, .glyph_index = 42000}, /* U+5047 假 */
    {.w_px = 25, .glyph_index = 42750}, /* U+504F 偏 */
    {.w_px = 25, .glyph_index = 43500}, /* U+505A 做 */
    {.w_px = 25, .glyph_index = 44250}, /* U+505C 停 */
    {.w_px = 25, .glyph_index = 45000}, /* U+5075 偵 */
    {.w_px = 25, .glyph_index = 45750}, /* U+5099 備 */
    {.w_px = 25, .glyph_index = 46500}, /* U+50B3 傳 */
    {.w_px = 25, .glyph_index = 47250}, /* U+50CF 像 */
    {.w_px = 25, .glyph_index = 48000}, /* U+5132 儲 */
    {.w_px = 25, .glyph_index = 48750}, /* U+5141 允 */
    {.w_px = 25, .glyph_index = 49500}, /* U+5143 元 */
    {.w_px = 25, .glyph_index = 50250}, /* U+5145 充 */
    {.w_px = 25, .glyph_index = 51000}, /* U+5148 先 */
    {.w_px = 25, .glyph_index = 51750}, /* U+5149 光 */
    {.w_px = 25, .glyph_index = 52500}, /* U+514D 免 */
    {.w_px = 25, .glyph_index = 53250}, /* U+5165 入 */
    {.w_px = 25, .glyph_index = 54000}, /* U+5167 內 */
    {.w_px = 25, .glyph_index = 54750}, /* U+5168 全 */
    {.w_px = 25, .glyph_index = 55500}, /* U+5169 兩 */
    {.w_px = 25, .glyph_index = 56250}, /* U+516B 八 */
    {.w_px = 25, .glyph_index = 57000}, /* U+516C 公 */
    {.w_px = 25, .glyph_index = 57750}, /* U+516D 六 */
    {.w_px = 25, .glyph_index = 58500}, /* U+5171 共 */
    {.w_px = 25, .glyph_index = 59250}, /* U+5176 其 */
    {.w_px = 25, .glyph_index = 60000}, /* U+5177 具 */
    {.w_px = 25, .glyph_index = 60750}, /* U+518D 再 */
    {.w_px = 25, .glyph_index = 61500}, /* U+51AC 冬 */
    {.w_px = 25, .glyph_index = 62250}, /* U+51B7 冷 */
    {.w_px = 25, .glyph_index = 63000}, /* U+51FA 出 */
    {.w_px = 25, .glyph_index = 63750}, /* U+5206 分 */
    {.w_px = 25, .glyph_index = 64500}, /* U+5207 切 */
    {.w_px = 25, .glyph_index = 65250}, /* U+5217 列 */
    {.w_px = 25, .glyph_index = 66000}, /* U+521D 初 */
    {.w_px = 25, .glyph_index = 66750}, /* U+5225 別 */
    {.w_px = 25, .glyph_index = 67500}, /* U+5229 利 */
    {.w_px = 25, .glyph_index = 68250}, /* U+522A 刪 */
    {.w_px = 25, .glyph_index = 69000}, /* U+5230 到 */
    {.w_px = 25, .glyph_index = 69750}, /* U+5236 制 */
    {.w_px = 25, .glyph_index = 70500}, /* U+5237 刷 */
    {.w_px = 25, .glyph_index = 71250}, /* U+523B 刻 */
    {.w_px = 25, .glyph_index = 72000}, /* U+5247 則 */
    {.w_px = 25, .glyph_index = 72750}, /* U+524D 前 */
    {.w_px = 25, .glyph_index = 73500}, /* U+526F 副 */
    {.w_px = 25, .glyph_index = 74250}, /* U+5272 割 */
    {.w_px = 25, .glyph_index = 75000}, /* U+529B 力 */
    {.w_px = 25, .glyph_index = 75750}, /* U+529F 功 */
    {.w_px = 25, .glyph_index = 76500}, /* U+52A0 加 */
    {.w_px = 25, .glyph_index = 77250}, /* U+52A9 助 */
    {.w_px = 25, .glyph_index = 78000}, /* U+52D5 動 */
    {.w_px = 25, .glyph_index = 78750}, /* U+52D9 務 */
    {.w_px = 25, .glyph_index = 79500}, /* U+5305 包 */
    {.w_px = 25, .glyph_index = 80250}, /* U+5316 化 */
    {.w_px = 25, .glyph_index = 81000}, /* U+5317 北 */
    {.w_px = 25, .glyph_index = 81750}, /* U+532F 匯 */
    {.w_px = 25, .glyph_index = 82500}, /* U+5340 區 */
    {.w_px = 25, .glyph_index = 83250}, /* U+5341 十 */
    {.w_px = 25, .glyph_index = 84000}, /* U+5343 千 */
    {.w_px = 25, .glyph_index = 84750}, /* U+5348 午 */
    {.w_px = 25, .glyph_index = 85500}, /* U+534A 半 */
    {.w_px = 25, .glyph_index = 86250}, /* U+5353 卓 */
    {.w_px = 25, .glyph_index = 87000}, /* U+5357 南 */
    {.w_px = 25, .glyph_index = 87750}, /* U+5361 卡 */
    {.w_px = 25, .glyph_index = 88500}, /* U+5371 危 */
    {.w_px = 25, .glyph_index = 89250}, /* U+5373 即 */
    {.w_px = 25, .glyph_index = 90000}, /* U+5378 卸 */
    {.w_px = 25, .glyph_index = 90750}, /* U+539F 原 */
    {.w_px = 25, .glyph_index = 91500}, /* U+53BB 去 */
    {.w_px = 25, .glyph_index = 92250}, /* U+53C3 參 */
    {.w_px = 25, .glyph_index = 93000}, /* U+53CA 及 */
    {.w_px = 25, .glyph_index = 93750}, /* U+53D6 取 */
    {.w_px = 25, .glyph_index = 94500}, /* U+53D7 受 */
    {.w_px = 25, .glyph_index = 95250}, /* U+53E2 叢 */
    {.w_px = 25, .glyph_index = 96000}, /* U+53EA 只 */
    {.w_px = 25, .glyph_index = 96750}, /* U+53EF 可 */
    {.w_px = 25, .glyph_index = 97500}, /* U+53F0 台 */
    {.w_px = 25, .glyph_index = 98250}, /* U+53F3 右 */
    {.w_px = 25, .glyph_index = 99000}, /* U+5404 各 */
    {.w_px = 25, .glyph_index = 99750}, /* U+5408 合 */
    {.w_px = 25, .glyph_index = 100500}, /* U+540C 同 */
    {.w_px = 25, .glyph_index = 101250}, /* U+540D 名 */
    {.w_px = 25, .glyph_index = 102000}, /* U+5426 否 */
    {.w_px = 25, .glyph_index = 102750}, /* U+542B 含 */
    {.w_px = 25, .glyph_index = 103500}, /* U+544A 告 */
    {.w_px = 25, .glyph_index = 104250}, /* U+547D 命 */
    {.w_px = 25, .glyph_index = 105000}, /* U+548C 和 */
    {.w_px = 25, .glyph_index = 105750}, /* U+54C1 品 */
    {.w_px = 25, .glyph_index = 106500}, /* U+552F 唯 */
    {.w_px = 25, .glyph_index = 107250}, /* U+5546 商 */
    {.w_px = 25, .glyph_index = 108000}, /* U+554F 問 */
    {.w_px = 25, .glyph_index = 108750}, /* U+555F 啟 */
    {.w_px = 25, .glyph_index = 109500}, /* U+559A 喚 */
    {.w_px = 25, .glyph_index = 110250}, /* U+55AE 單 */
    {.w_px = 25, .glyph_index = 111000}, /* U+55CE 嗎 */
    {.w_px = 25, .glyph_index = 111750}, /* U+5617 嘗 */
    {.w_px = 25, .glyph_index = 112500}, /* U+5668 器 */
    {.w_px = 25, .glyph_index = 113250}, /* U+56B4 嚴 */
    {.w_px = 25, .glyph_index = 114000}, /* U+56DB 四 */
    {.w_px = 25, .glyph_index = 114750}, /* U+56DE 回 */
    {.w_px = 25, .glyph_index = 115500}, /* U+56E0 因 */
    {.w_px = 25, .glyph_index = 116250}, /* U+570D 圍 */
    {.w_px = 25, .glyph_index = 117000}, /* U+5713 圓 */
    {.w_px = 25, .glyph_index = 117750}, /* U+5716 圖 */
    {.w_px = 25, .glyph_index = 118500}, /* U+5728 在 */
    {.w_px = 25, .glyph_index = 119250}, /* U+5730 地 */
    {.w_px = 25, .glyph_index = 120000}, /* U+5740 址 */
    {.w_px = 25, .glyph_index = 120750}, /* U+5747 均 */
    {.w_px = 25, .glyph_index = 121500}, /* U+578B 型 */
    {.w_px = 25, .glyph_index = 122250}, /* U+57DF 域 */
    {.w_px = 25, .glyph_index = 123000}, /* U+57F7 執 */
    {.w_px = 25, .glyph_index = 123750}, /* U+57FA 基 */
    {.w_px = 25, .glyph_index = 124500}, /* U+5831 報 */
    {.w_px = 25, .glyph_index = 125250}, /* U+584A 塊 */
    {.w_px = 25, .glyph_index = 126000}, /* U+58D3 壓 */
    {.w_px = 25, .glyph_index = 126750}, /* U+58DE 壞 */
    {.w_px = 25, .glyph_index = 127500}, /* U+58EC 壬 */
    {.w_px = 25, .glyph_index = 128250}, /* U+58F9 壹 */
    {.w_px = 25, .glyph_index = 129000}, /* U+58FD 壽 */
    {.w_px = 25, .glyph_index = 129750}, /* U+590F 夏 */
    {.w_px = 25, .glyph_index = 130500}, /* U+5916 外 */
    {.w_px = 25, .glyph_index = 131250}, /* U+591A 多 */
    {.w_px = 25, .glyph_index = 132000}, /* U+5927 大 */
    {.w_px = 25, .glyph_index = 132750}, /* U+5929 天 */
    {.w_px = 25, .glyph_index = 133500}, /* U+592A 太 */
    {.w_px = 25, .glyph_index = 134250}, /* U+5931 失 */
    {.w_px = 25, .glyph_index = 135000}, /* U+593E 夾 */
    {.w_px = 25, .glyph_index = 135750}, /* U+5957 套 */
    {.w_px = 25, .glyph_index = 136500}, /* U+5979 她 */
    {.w_px = 25, .glyph_index = 137250}, /* U+597D 好 */
    {.w_px = 25, .glyph_index = 138000}, /* U+5982 如 */
    {.w_px = 25, .glyph_index = 138750}, /* U+59CB 始 */
    {.w_px = 25, .glyph_index = 139500}, /* U+5B57 字 */
    {.w_px = 25, .glyph_index = 140250}, /* U+5B58 存 */
    {.w_px = 25, .glyph_index = 141000}, /* U+5B83 它 */
    {.w_px = 25, .glyph_index = 141750}, /* U+5B89 安 */
    {.w_px = 25, .glyph_index = 142500}, /* U+5B8C 完 */
    {.w_px = 25, .glyph_index = 143250}, /* U+5B9A 定 */
    {.w_px = 25, .glyph_index = 144000}, /* U+5BB9 容 */
    {.w_px = 25, .glyph_index = 144750}, /* U+5BC6 密 */
    {.w_px = 25, .glyph_index = 145500}, /* U+5BE6 實 */
    {.w_px = 25, .glyph_index = 146250}, /* U+5BEB 寫 */
    {.w_px = 25, .glyph_index = 147000}, /* U+5BEC 寬 */
    {.w_px = 25, .glyph_index = 147750}, /* U+5C01 封 */
    {.w_px = 25, .glyph_index = 148500}, /* U+5C07 將 */
    {.w_px = 25, .glyph_index = 149250}, /* U+5C0B 尋 */
    {.w_px = 25, .glyph_index = 150000}, /* U+5C0D 對 */
    {.w_px = 25, .glyph_index = 150750}, /* U+5C0F 小 */
    {.w_px = 25, .glyph_index = 151500}, /* U+5C11 少 */
    {.w_px = 25, .glyph_index = 152250}, /* U+5C31 就 */
    {.w_px = 25, .glyph_index = 153000}, /* U+5C64 層 */
    {.w_px = 25, .glyph_index = 153750}, /* U+5C6C 屬 */
    {.w_px = 25, .glyph_index = 154500}, /* U+5DE5 工 */
    {.w_px = 25, .glyph_index = 155250}, /* U+5DE6 左 */
    {.w_px = 25, .glyph_index = 156000}, /* U+5DF1 己 */
    {.w_px = 25, .glyph_index = 156750}, /* U+5DF2 已 */
    {.w_px = 25, .glyph_index = 157500}, /* U+5E33 帳 */
    {.w_px = 25, .glyph_index = 158250}, /* U+5E36 帶 */
    {.w_px = 25, .glyph_index = 159000}, /* U+5E38 常 */
    {.w_px = 25, .glyph_index = 159750}, /* U+5E55 幕 */
    {.w_px = 25, .glyph_index = 160500}, /* U+5E6B 幫 */
    {.w_px = 25, .glyph_index = 161250}, /* U+5E73 平 */
    {.w_px = 25, .glyph_index = 162000}, /* U+5E74 年 */
    {.w_px = 25, .glyph_index = 162750}, /* U+5E9A 庚 */
    {.w_px = 25, .glyph_index = 163500}, /* U+5EA6 度 */
    {.w_px = 25, .glyph_index = 164250}, /* U+5EA7 座 */
    {.w_px = 25, .glyph_index = 165000}, /* U+5EE0 廠 */
    {.w_px = 25, .glyph_index = 165750}, /* U+5EFA 建 */
    {.w_px = 25, .glyph_index = 166500}, /* U+5F0F 式 */
    {.w_px = 25, .glyph_index = 167250}, /* U+5F37 強 */
    {.w_px = 25, .glyph_index = 168000}, /* U+5F62 形 */
    {.w_px = 25, .glyph_index = 168750}, /* U+5F69 彩 */
    {.w_px = 25, .glyph_index = 169500}, /* U+5F71 影 */
    {.w_px = 25, .glyph_index = 170250}, /* U+5F85 待 */
    {.w_px = 25, .glyph_index = 171000}, /* U+5F88 很 */
    {.w_px = 25, .glyph_index = 171750}, /* U+5F8C 後 */
    {.w_px = 25, .glyph_index = 172500}, /* U+5F91 徑 */
    {.w_px = 25, .glyph_index = 173250}, /* U+5F97 得 */
    {.w_px = 25, .glyph_index = 174000}, /* U+5F9E 從 */
    {.w_px = 25, .glyph_index = 174750}, /* U+5FA9 復 */
    {.w_px = 25, .glyph_index = 175500}, /* U+5FC3 心 */
    {.w_px = 25, .glyph_index = 176250}, /* U+5FC5 必 */
    {.w_px = 25, .glyph_index = 177000}, /* U+5FEB 快 */
    {.w_px = 25, .glyph_index = 177750}, /* U+6027 性 */
    {.w_px = 25, .glyph_index = 178500}, /* U+6062 恢 */
    {.w_px = 25, .glyph_index = 179250}, /* U+606F 息 */
    {.w_px = 25, .glyph_index = 180000}, /* U+60F3 想 */
    {.w_px = 25, .glyph_index = 180750}, /* U+610F 意 */
    {.w_px = 25, .glyph_index = 181500}, /* U+611F 感 */
    {.w_px = 25, .glyph_index = 182250}, /* U+614B 態 */
    {.w_px = 25, .glyph_index = 183000}, /* U+6162 慢 */
    {.w_px = 25, .glyph_index = 183750}, /* U+61B6 憶 */
    {.w_px = 25, .glyph_index = 184500}, /* U+61C9 應 */
    {.w_px = 25, .glyph_index = 185250}, /* U+620A 戊 */
    {.w_px = 25, .glyph_index = 186000}, /* U+6210 成 */
    {.w_px = 25, .glyph_index = 186750}, /* U+6211 我 */
    {.w_px = 25, .glyph_index = 187500}, /* U+6216 或 */
    {.w_px = 25, .glyph_index = 188250}, /* U+622A 截 */
    {.w_px = 25, .glyph_index = 189000}, /* U+6232 戲 */
    {.w_px = 25, .glyph_index = 189750}, /* U+6240 所 */
    {.w_px = 25, .glyph_index = 190500}, /* U+6247 扇 */
    {.w_px = 25, .glyph_index = 191250}, /* U+624B 手 */
    {.w_px = 25, .glyph_index = 192000}, /* U+624D 才 */
    {.w_px = 25, .glyph_index = 192750}, /* U+627E 找 */
    {.w_px = 25, .glyph_index = 193500}, /* U+628A 把 */
    {.w_px = 25, .glyph_index = 194250}, /* U+62BD 抽 */
    {.w_px = 25, .glyph_index = 195000}, /* U+62C6 拆 */
    {.w_px = 25, .glyph_index = 195750}, /* U+62D2 拒 */
    {.w_px = 25, .glyph_index = 196500}, /* U+62D4 拔 */
    {.w_px = 25, .glyph_index = 197250}, /* U+62FE 拾 */
    {.w_px = 25, .glyph_index = 198000}, /* U+62FF 拿 */
    {.w_px = 25, .glyph_index = 198750}, /* U+6307 指 */
    {.w_px = 25, .glyph_index = 199500}, /* U+6309 按 */
    {.w_px = 25, .glyph_index = 200250}, /* U+634C 捌 */
    {.w_px = 25, .glyph_index = 201000}, /* U+6383 掃 */
    {.w_px = 25, .glyph_index = 201750}, /* U+6389 掉 */
    {.w_px = 25, .glyph_index = 202500}, /* U+6392 排 */
    {.w_px = 25, .glyph_index = 203250}, /* U+639B 掛 */
    {.w_px = 25, .glyph_index = 204000}, /* U+63A2 探 */
    {.w_px = 25, .glyph_index = 204750}, /* U+63A5 接 */
    {.w_px = 25, .glyph_index = 205500}, /* U+63A7 控 */
    {.w_px = 25, .glyph_index = 206250}, /* U+63CF 描 */
    {.w_px = 25, .glyph_index = 207000}, /* U+63D0 提 */
    {.w_px = 25, .glyph_index = 207750}, /* U+63D2 插 */
    {.w_px = 25, .glyph_index = 208500}, /* U+63DB 換 */
    {.w_px = 25, .glyph_index = 209250}, /* U+63F4 援 */
    {.w_px = 25, .glyph_index = 210000}, /* U+640D 損 */
    {.w_px = 25, .glyph_index = 210750}, /* U+641C 搜 */
    {.w_px = 25, .glyph_index = 211500}, /* U+642C 搬 */
    {.w_px = 25, .glyph_index = 212250}, /* U+642D 搭 */
    {.w_px = 25, .glyph_index = 213000}, /* U+64C7 擇 */
    {.w_px = 25, .glyph_index = 213750}, /* U+64CD 操 */
    {.w_px = 25, .glyph_index = 214500}, /* U+64EC 擬 */
    {.w_px = 25, .glyph_index = 215250}, /* U+64F4 擴 */
    {.w_px = 25, .glyph_index = 216000}, /* U+652F 支 */
    {.w_px = 25, .glyph_index = 216750}, /* U+6536 收 */
    {.w_px = 25, .glyph_index = 217500}, /* U+6539 改 */
    {.w_px = 25, .glyph_index = 218250}, /* U+653E 放 */
    {.w_px = 25, .glyph_index = 219000}, /* U+6548 效 */
    {.w_px = 25, .glyph_index = 219750}, /* U+6557 敗 */
    {.w_px = 25, .glyph_index = 220500}, /* U+6574 整 */
    {.w_px = 25, .glyph_index = 221250}, /* U+6578 數 */
    {.w_px = 25, .glyph_index = 222000}, /* U+6587 文 */
    {.w_px = 25, .glyph_index = 222750}, /* U+6599 料 */
    {.w_px = 25, .glyph_index = 223500}, /* U+65B0 新 */
    {.w_px = 25, .glyph_index = 224250}, /* U+65B7 斷 */
    {.w_px = 25, .glyph_index = 225000}, /* U+65B9 方 */
    {.w_px = 25, .glyph_index = 225750}, /* U+65BC 於 */
    {.w_px = 25, .glyph_index = 226500}, /* U+65E5 日 */
    {.w_px = 25, .glyph_index = 227250}, /* U+65E9 早 */
    {.w_px = 25, .glyph_index = 228000}, /* U+660E 明 */
    {.w_px = 25, .glyph_index = 228750}, /* U+661F 星 */
    {.w_px = 25, .glyph_index = 229500}, /* U+6620 映 */
    {.w_px = 25, .glyph_index = 230250}, /* U+6625 春 */
    {.w_px = 25, .glyph_index = 231000}, /* U+6628 昨 */
    {.w_px = 25, .glyph_index = 231750}, /* U+662F 是 */
    {.w_px = 25, .glyph_index = 232500}, /* U+6642 時 */
    {.w_px = 25, .glyph_index = 233250}, /* U+665A 晚 */
    {.w_px = 25, .glyph_index = 234000}, /* U+666F 景 */
    {.w_px = 25, .glyph_index = 234750}, /* U+6676 晶 */
    {.w_px = 25, .glyph_index = 235500}, /* U+6697 暗 */
    {.w_px = 25, .glyph_index = 236250}, /* U+66AB 暫 */
    {.w_px = 25, .glyph_index = 237000}, /* U+66F4 更 */
    {.w_px = 25, .glyph_index = 237750}, /* U+66FF 替 */
    {.w_px = 25, .glyph_index = 238500}, /* U+6700 最 */
    {.w_px = 25, .glyph_index = 239250}, /* U+6703 會 */
    {.w_px = 25, .glyph_index = 240000}, /* U+6708 月 */
    {.w_px = 25, .glyph_index = 240750}, /* U+6709 有 */
    {.w_px = 25, .glyph_index = 241500}, /* U+670D 服 */
    {.w_px = 25, .glyph_index = 242250}, /* U+671F 期 */
    {.w_px = 25, .glyph_index = 243000}, /* U+672A 未 */
    {.w_px = 25, .glyph_index = 243750}, /* U+672C 本 */
    {.w_px = 25, .glyph_index = 244500}, /* U+675F 束 */
    {.w_px = 25, .glyph_index = 245250}, /* U+6771 東 */
    {.w_px = 25, .glyph_index = 246000}, /* U+677F 板 */
    {.w_px = 25, .glyph_index = 246750}, /* U+6790 析 */
    {.w_px = 25, .glyph_index = 247500}, /* U+679C 果 */
    {.w_px = 25, .glyph_index = 248250}, /* U+67D2 柒 */
    {.w_px = 25, .glyph_index = 249000}, /* U+67E5 查 */
    {.w_px = 25, .glyph_index = 249750}, /* U+6821 校 */
    {.w_px = 25, .glyph_index = 250500}, /* U+6838 核 */
    {.w_px = 25, .glyph_index = 251250}, /* U+6839 根 */
    {.w_px = 25, .glyph_index = 252000}, /* U+683C 格 */
    {.w_px = 25, .glyph_index = 252750}, /* U+6848 案 */
    {.w_px = 25, .glyph_index = 253500}, /* U+684C 桌 */
    {.w_px = 25, .glyph_index = 254250}, /* U+696D 業 */
    {.w_px = 25, .glyph_index = 255000}, /* U+69FD 槽 */
    {.w_px = 25, .glyph_index = 255750}, /* U+6A19 標 */
    {.w_px = 25, .glyph_index = 256500}, /* U+6A21 模 */
    {.w_px = 25, .glyph_index = 257250}, /* U+6A23 樣 */
    {.w_px = 25, .glyph_index = 258000}, /* U+6A5F 機 */
    {.w_px = 25, .glyph_index = 258750}, /* U+6A94 檔 */
    {.w_px = 25, .glyph_index = 259500}, /* U+6AA2 檢 */
    {.w_px = 25, .glyph_index = 260250}, /* U+6B0A 權 */
    {.w_px = 25, .glyph_index = 261000}, /* U+6B21 次 */
    {.w_px = 25, .glyph_index = 261750}, /* U+6B61 歡 */
    {.w_px = 25, .glyph_index = 262500}, /* U+6B62 止 */
    {.w_px = 25, .glyph_index = 263250}, /* U+6B63 正 */
    {.w_px = 25, .glyph_index = 264000}, /* U+6B65 步 */
    {.w_px = 25, .glyph_index = 264750}, /* U+6BB5 段 */
    {.w_px = 25, .glyph_index = 265500}, /* U+6BC0 毀 */
    {.w_px = 25, .glyph_index = 266250}, /* U+6BCF 每 */
    {.w_px = 25, .glyph_index = 267000}, /* U+6BD4 比 */
    {.w_px = 25, .glyph_index = 267750}, /* U+6C23 氣 */
    {.w_px = 25, .glyph_index = 268500}, /* U+6C38 永 */
    {.w_px = 25, .glyph_index = 269250}, /* U+6C42 求 */
    {.w_px = 25, .glyph_index = 270000}, /* U+6C60 池 */
    {.w_px = 25, .glyph_index = 270750}, /* U+6C92 沒 */
    {.w_px = 25, .glyph_index = 271500}, /* U+6CD5 法 */
    {.w_px = 25, .glyph_index = 272250}, /* U+6CE8 注 */
    {.w_px = 25, .glyph_index = 273000}, /* U+6D1E 洞 */
    {.w_px = 25, .glyph_index = 273750}, /* U+6D41 流 */
    {.w_px = 25, .glyph_index = 274500}, /* U+6D88 消 */
    {.w_px = 25, .glyph_index = 275250}, /* U+6DF7 混 */
    {.w_px = 25, .glyph_index = 276000}, /* U+6E05 清 */
    {.w_px = 25, .glyph_index = 276750}, /* U+6E2C 測 */
    {.w_px = 25, .glyph_index = 277500}, /* U+6E4A 湊 */
    {.w_px = 25, .glyph_index = 278250}, /* U+6E90 源 */
    {.w_px = 25, .glyph_index = 279000}, /* U+6E96 準 */
    {.w_px = 25, .glyph_index = 279750}, /* U+6EAB 溫 */
    {.w_px = 25, .glyph_index = 280500}, /* U+6EFF 滿 */
    {.w_px = 25, .glyph_index = 281250}, /* U+6F0F 漏 */
    {.w_px = 25, .glyph_index = 282000}, /* U+7070 灰 */
    {.w_px = 25, .glyph_index = 282750}, /* U+70BA 為 */
    {.w_px = 25, .glyph_index = 283500}, /* U+7121 無 */
    {.w_px = 25, .glyph_index = 284250}, /* U+7194 熔 */
    {.w_px = 25, .glyph_index = 285000}, /* U+71B1 熱 */
    {.w_px = 25, .glyph_index = 285750}, /* U+71D2 燒 */
    {.w_px = 25, .glyph_index = 286500}, /* U+7247 片 */
    {.w_px = 25, .glyph_index = 287250}, /* U+7248 版 */
    {.w_px = 25, .glyph_index = 288000}, /* U+7259 牙 */
    {.w_px = 25, .glyph_index = 288750}, /* U+7279 特 */
    {.w_px = 25, .glyph_index = 289500}, /* U+72C0 狀 */
    {.w_px = 25, .glyph_index = 290250}, /* U+7368 獨 */
    {.w_px = 25, .glyph_index = 291000}, /* U+7387 率 */
    {.w_px = 25, .glyph_index = 291750}, /* U+7396 玖 */
    {.w_px = 25, .glyph_index = 292500}, /* U+73FE 現 */
    {.w_px = 25, .glyph_index = 293250}, /* U+7406 理 */
    {.w_px = 25, .glyph_index = 294000}, /* U+751A 甚 */
    {.w_px = 25, .glyph_index = 294750}, /* U+751F 生 */
    {.w_px = 25, .glyph_index = 295500}, /* U+7522 產 */
    {.w_px = 25, .glyph_index = 296250}, /* U+7528 用 */
    {.w_px = 25, .glyph_index = 297000}, /* U+7532 甲 */
    {.w_px = 25, .glyph_index = 297750}, /* U+7559 留 */
    {.w_px = 25, .glyph_index = 298500}, /* U+756B 畫 */
    {.w_px = 25, .glyph_index = 299250}, /* U+7570 異 */
    {.w_px = 25, .glyph_index = 300000}, /* U+7576 當 */
    {.w_px = 25, .glyph_index = 300750}, /* U+7678 癸 */
    {.w_px = 25, .glyph_index = 301500}, /* U+767B 登 */
    {.w_px = 25, .glyph_index = 302250}, /* U+767C 發 */
    {.w_px = 25, .glyph_index = 303000}, /* U+767D 白 */
    {.w_px = 25, .glyph_index = 303750}, /* U+767E 百 */
    {.w_px = 25, .glyph_index = 304500}, /* U+7684 的 */
    {.w_px = 25, .glyph_index = 305250}, /* U+7686 皆 */
    {.w_px = 25, .glyph_index = 306000}, /* U+76EE 目 */
    {.w_px = 25, .glyph_index = 306750}, /* U+76F4 直 */
    {.w_px = 25, .glyph_index = 307500}, /* U+76F8 相 */
    {.w_px = 25, .glyph_index = 308250}, /* U+770B 看 */
    {.w_px = 25, .glyph_index = 309000}, /* U+771F 真 */
    {.w_px = 25, .glyph_index = 309750}, /* U+77E5 知 */
    {.w_px = 25, .glyph_index = 310500}, /* U+77ED 短 */
    {.w_px = 25, .glyph_index = 311250}, /* U+7834 破 */
    {.w_px = 25, .glyph_index = 312000}, /* U+786C 硬 */
    {.w_px = 25, .glyph_index = 312750}, /* U+789F 碟 */
    {.w_px = 25, .glyph_index = 313500}, /* U+78B0 碰 */
    {.w_px = 25, .glyph_index = 314250}, /* U+78BA 確 */
    {.w_px = 25, .glyph_index = 315000}, /* U+78BC 碼 */
    {.w_px = 25, .glyph_index = 315750}, /* U+78C1 磁 */
    {.w_px = 25, .glyph_index = 316500}, /* U+790E 礎 */
    {.w_px = 25, .glyph_index = 317250}, /* U+793A 示 */
    {.w_px = 25, .glyph_index = 318000}, /* U+7981 禁 */
    {.w_px = 25, .glyph_index = 318750}, /* U+79CB 秋 */
    {.w_px = 25, .glyph_index = 319500}, /* U+79D2 秒 */
    {.w_px = 25, .glyph_index = 320250}, /* U+79FB 移 */
    {.w_px = 25, .glyph_index = 321000}, /* U+7A0B 程 */
    {.w_px = 25, .glyph_index = 321750}, /* U+7A0D 稍 */
    {.w_px = 25, .glyph_index = 322500}, /* U+7A2E 種 */
    {.w_px = 25, .glyph_index = 323250}, /* U+7A31 稱 */
    {.w_px = 25, .glyph_index = 324000}, /* U+7A7A 空 */
    {.w_px = 25, .glyph_index = 324750}, /* U+7ACB 立 */
    {.w_px = 25, .glyph_index = 325500}, /* U+7B26 符 */
    {.w_px = 25, .glyph_index = 326250}, /* U+7B2C 第 */
    {.w_px = 25, .glyph_index = 327000}, /* U+7B49 等 */
    {.w_px = 25, .glyph_index = 327750}, /* U+7B97 算 */
    {.w_px = 25, .glyph_index = 328500}, /* U+7BA1 管 */
    {.w_px = 25, .glyph_index = 329250}, /* U+7BC0 節 */
    {.w_px = 25, .glyph_index = 330000}, /* U+7BC4 範 */
    {.w_px = 25, .glyph_index = 330750}, /* U+7C21 簡 */
    {.w_px = 25, .glyph_index = 331500}, /* U+7C3F 簿 */
    {.w_px = 25, .glyph_index = 332250}, /* U+7CFB 系 */
    {.w_px = 25, .glyph_index = 333000}, /* U+7D00 紀 */
    {.w_px = 25, .glyph_index = 333750}, /* U+7D04 約 */
    {.w_px = 25, .glyph_index = 334500}, /* U+7D1A 級 */
    {.w_px = 25, .glyph_index = 335250}, /* U+7D30 細 */
    {.w_px = 25, .glyph_index = 336000}, /* U+7D42 終 */
    {.w_px = 25, .glyph_index = 336750}, /* U+7D44 組 */
    {.w_px = 25, .glyph_index = 337500}, /* U+7D50 結 */
    {.w_px = 25, .glyph_index = 338250}, /* U+7D55 絕 */
    {.w_px = 25, .glyph_index = 339000}, /* U+7D71 統 */
    {.w_px = 25, .glyph_index = 339750}, /* U+7D72 絲 */
    {.w_px = 25, .glyph_index = 340500}, /* U+7D93 經 */
    {.w_px = 25, .glyph_index = 341250}, /* U+7DAD 維 */
    {.w_px = 25, .glyph_index = 342000}, /* U+7DB2 網 */
    {.w_px = 25, .glyph_index = 342750}, /* U+7DDA 線 */
    {.w_px = 25, .glyph_index = 343500}, /* U+7E3D 總 */
    {.w_px = 25, .glyph_index = 344250}, /* U+7E41 繁 */
    {.w_px = 25, .glyph_index = 345000}, /* U+7E7C 繼 */
    {.w_px = 25, .glyph_index = 345750}, /* U+7E8C 續 */
    {.w_px = 25, .glyph_index = 346500}, /* U+7F3A 缺 */
    {.w_px = 25, .glyph_index = 347250}, /* U+7F6E 置 */
    {.w_px = 25, .glyph_index = 348000}, /* U+8005 者 */
    {.w_px = 25, .glyph_index = 348750}, /* U+800C 而 */
    {.w_px = 25, .glyph_index = 349500}, /* U+8017 耗 */
    {.w_px = 25, .glyph_index = 350250}, /* U+8072 聲 */
    {.w_px = 25, .glyph_index = 351000}, /* U+807D 聽 */
    {.w_px = 25, .glyph_index = 351750}, /* U+8086 肆 */
    {.w_px = 25, .glyph_index = 352500}, /* U+80CC 背 */
    {.w_px = 25, .glyph_index = 353250}, /* U+80FD 能 */
    {.w_px = 25, .glyph_index = 354000}, /* U+8166 腦 */
    {.w_px = 25, .glyph_index = 354750}, /* U+81EA 自 */
    {.w_px = 25, .glyph_index = 355500}, /* U+81F3 至 */
    {.w_px = 25, .glyph_index = 356250}, /* U+81F4 致 */
    {.w_px = 25, .glyph_index = 357000}, /* U+8207 與 */
    {.w_px = 25, .glyph_index = 357750}, /* U+820A 舊 */
    {.w_px = 25, .glyph_index = 358500}, /* U+822C 般 */
    {.w_px = 25, .glyph_index = 359250}, /* U+826F 良 */
    {.w_px = 25, .glyph_index = 360000}, /* U+8272 色 */
    {.w_px = 25, .glyph_index = 360750}, /* U+82F1 英 */
    {.w_px = 25, .glyph_index = 361500}, /* U+842C 萬 */
    {.w_px = 25, .glyph_index = 362250}, /* U+85CD 藍 */
    {.w_px = 25, .glyph_index = 363000}, /* U+8655 處 */
    {.w_px = 25, .glyph_index = 363750}, /* U+865B 虛 */
    {.w_px = 25, .glyph_index = 364500}, /* U+865F 號 */
    {.w_px = 25, .glyph_index = 365250}, /* U+87A2 螢 */
    {.w_px = 25, .glyph_index = 366000}, /* U+884C 行 */
    {.w_px = 25, .glyph_index = 366750}, /* U+8868 表 */
    {.w_px = 25, .glyph_index = 367500}, /* U+88AB 被 */
    {.w_px = 25, .glyph_index = 368250}, /* U+88DC 補 */
    {.w_px = 25, .glyph_index = 369000}, /* U+88DD 裝 */
    {.w_px = 25, .glyph_index = 369750}, /* U+88E1 裡 */
    {.w_px = 25, .glyph_index = 370500}, /* U+88FD 製 */
    {.w_px = 25, .glyph_index = 371250}, /* U+8907 複 */
    {.w_px = 25, .glyph_index = 372000}, /* U+897F 西 */
    {.w_px = 25, .glyph_index = 372750}, /* U+8981 要 */
    {.w_px = 25, .glyph_index = 373500}, /* U+898B 見 */
    {.w_px = 25, .glyph_index = 374250}, /* U+898F 規 */
    {.w_px = 25, .glyph_index = 375000}, /* U+89BD 覽 */
    {.w_px = 25, .glyph_index = 375750}, /* U+89C0 觀 */
    {.w_px = 25, .glyph_index = 376500}, /* U+89E3 解 */
    {.w_px = 25, .glyph_index = 377250}, /* U+89F8 觸 */
    {.w_px = 25, .glyph_index = 378000}, /* U+8A00 言 */
    {.w_px = 25, .glyph_index = 378750}, /* U+8A02 訂 */
    {.w_px = 25, .glyph_index = 379500}, /* U+8A08 計 */
    {.w_px = 25, .glyph_index = 380250}, /* U+8A0A 訊 */
    {.w_px = 25, .glyph_index = 381000}, /* U+8A18 記 */
    {.w_px = 25, .glyph_index = 381750}, /* U+8A2D 設 */
    {.w_px = 25, .glyph_index = 382500}, /* U+8A31 許 */
    {.w_px = 25, .glyph_index = 383250}, /* U+8A3B 註 */
    {.w_px = 25, .glyph_index = 384000}, /* U+8A62 詢 */
    {.w_px = 25, .glyph_index = 384750}, /* U+8A66 試 */
    {.w_px = 25, .glyph_index = 385500}, /* U+8A71 話 */
    {.w_px = 25, .glyph_index = 386250}, /* U+8A73 詳 */
    {.w_px = 25, .glyph_index = 387000}, /* U+8A8C 誌 */
    {.w_px = 25, .glyph_index = 387750}, /* U+8A8D 認 */
    {.w_px = 25, .glyph_index = 388500}, /* U+8A9E 語 */
    {.w_px = 25, .glyph_index = 389250}, /* U+8AA4 誤 */
    {.w_px = 25, .glyph_index = 390000}, /* U+8AAA 說 */
    {.w_px = 25, .glyph_index = 390750}, /* U+8ABF 調 */
    {.w_px = 25, .glyph_index = 391500}, /* U+8ACB 請 */
    {.w_px = 25, .glyph_index = 392250}, /* U+8B1D 謝 */
    {.w_px = 25, .glyph_index = 393000}, /* U+8B49 證 */
    {.w_px = 25, .glyph_index = 393750}, /* U+8B66 警 */
    {.w_px = 25, .glyph_index = 394500}, /* U+8B70 議 */
    {.w_px = 25, .glyph_index = 395250}, /* U+8B77 護 */
    {.w_px = 25, .glyph_index = 396000}, /* U+8B80 讀 */
    {.w_px = 25, .glyph_index = 396750}, /* U+8B8A 變 */
    {.w_px = 25, .glyph_index = 397500}, /* U+8B93 讓 */
    {.w_px = 25, .glyph_index = 398250}, /* U+8CB3 貳 */
    {.w_px = 25, .glyph_index = 399000}, /* U+8CBB 費 */
    {.w_px = 25, .glyph_index = 399750}, /* U+8CC7 資 */
    {.w_px = 25, .glyph_index = 400500}, /* U+8D70 走 */
    {.w_px = 25, .glyph_index = 401250}, /* U+8D77 起 */
    {.w_px = 25, .glyph_index = 402000}, /* U+8D85 超 */
    {.w_px = 25, .glyph_index = 402750}, /* U+8DB3 足 */
    {.w_px = 25, .glyph_index = 403500}, /* U+8DEF 路 */
    {.w_px = 25, .glyph_index = 404250}, /* U+8DF3 跳 */
    {.w_px = 25, .glyph_index = 405000}, /* U+8EDF 軟 */
    {.w_px = 25, .glyph_index = 405750}, /* U+8F03 較 */
    {.w_px = 25, .glyph_index = 406500}, /* U+8F09 載 */
    {.w_px = 25, .glyph_index = 407250}, /* U+8F15 輕 */
    {.w_px = 25, .glyph_index = 408000}, /* U+8F38 輸 */
    {.w_px = 25, .glyph_index = 408750}, /* U+8F49 轉 */
    {.w_px = 25, .glyph_index = 409500}, /* U+8F9B 辛 */
    {.w_px = 25, .glyph_index = 410250}, /* U+8FCE 迎 */
    {.w_px = 25, .glyph_index = 411000}, /* U+8FD4 返 */
    {.w_px = 25, .glyph_index = 411750}, /* U+9000 退 */
    {.w_px = 25, .glyph_index = 412500}, /* U+9001 送 */
    {.w_px = 25, .glyph_index = 413250}, /* U+9010 逐 */
    {.w_px = 25, .glyph_index = 414000}, /* U+9014 途 */
    {.w_px = 25, .glyph_index = 414750}, /* U+9019 這 */
    {.w_px = 25, .glyph_index = 415500}, /* U+901A 通 */
    {.w_px = 25, .glyph_index = 416250}, /* U+901F 速 */
    {.w_px = 25, .glyph_index = 417000}, /* U+9020 造 */
    {.w_px = 25, .glyph_index = 417750}, /* U+9023 連 */
    {.w_px = 25, .glyph_index = 418500}, /* U+9031 週 */
    {.w_px = 25, .glyph_index = 419250}, /* U+9032 進 */
    {.w_px = 25, .glyph_index = 420000}, /* U+904A 遊 */
    {.w_px = 25, .glyph_index = 420750}, /* U+904B 運 */
    {.w_px = 25, .glyph_index = 421500}, /* U+904E 過 */
    {.w_px = 25, .glyph_index = 422250}, /* U+9053 道 */
    {.w_px = 25, .glyph_index = 423000}, /* U+9069 適 */
    {.w_px = 25, .glyph_index = 423750}, /* U+9078 選 */
    {.w_px = 25, .glyph_index = 424500}, /* U+9084 還 */
    {.w_px = 25, .glyph_index = 425250}, /* U+908A 邊 */
    {.w_px = 25, .glyph_index = 426000}, /* U+90E8 部 */
    {.w_px = 25, .glyph_index = 426750}, /* U+90FD 都 */
    {.w_px = 25, .glyph_index = 427500}, /* U+914D 配 */
    {.w_px = 25, .glyph_index = 428250}, /* U+9192 醒 */
    {.w_px = 25, .glyph_index = 429000}, /* U+91CD 重 */
    {.w_px = 25, .glyph_index = 429750}, /* U+91CF 量 */
    {.w_px = 25, .glyph_index = 430500}, /* U+91D1 金 */
    {.w_px = 25, .glyph_index = 431250}, /* U+9215 鈕 */
    {.w_px = 25, .glyph_index = 432000}, /* U+9304 錄 */
    {.w_px = 25, .glyph_index = 432750}, /* U+932F 錯 */
    {.w_px = 25, .glyph_index = 433500}, /* U+9375 鍵 */
    {.w_px = 25, .glyph_index = 434250}, /* U+9396 鎖 */
    {.w_px = 25, .glyph_index = 435000}, /* U+9418 鐘 */
    {.w_px = 25, .glyph_index = 435750}, /* U+9470 鑰 */
    {.w_px = 25, .glyph_index = 436500}, /* U+9577 長 */
    {.w_px = 25, .glyph_index = 437250}, /* U+9589 閉 */
    {.w_px = 25, .glyph_index = 438000}, /* U+958B 開 */
    {.w_px = 25, .glyph_index = 438750}, /* U+9593 間 */
    {.w_px = 25, .glyph_index = 439500}, /* U+95DC 關 */
    {.w_px = 25, .glyph_index = 440250}, /* U+964D 降 */
    {.w_px = 25, .glyph_index = 441000}, /* U+9650 限 */
    {.w_px = 25, .glyph_index = 441750}, /* U+9664 除 */
    {.w_px = 25, .glyph_index = 442500}, /* U+9678 陸 */
    {.w_px = 25, .glyph_index = 443250}, /* U+968E 階 */
    {.w_px = 25, .glyph_index = 444000}, /* U+969B 際 */
    {.w_px = 25, .glyph_index = 444750}, /* U+96AA 險 */
    {.w_px = 25, .glyph_index = 445500}, /* U+96C6 集 */
    {.w_px = 25, .glyph_index = 446250}, /* U+96DC 雜 */
    {.w_px = 25, .glyph_index = 447000}, /* U+96F6 零 */
    {.w_px = 25, .glyph_index = 447750}, /* U+96FB 電 */
    {.w_px = 25, .glyph_index = 448500}, /* U+9700 需 */
    {.w_px = 25, .glyph_index = 449250}, /* U+975E 非 */
    {.w_px = 25, .glyph_index = 450000}, /* U+9762 面 */
    {.w_px = 25, .glyph_index = 450750}, /* U+97CC 韌 */
    {.w_px = 25, .glyph_index = 451500}, /* U+97D3 韓 */
    {.w_px = 25, .glyph_index = 452250}, /* U+97F3 音 */
    {.w_px = 25, .glyph_index = 453000}, /* U+97FF 響 */
    {.w_px = 25, .glyph_index = 453750}, /* U+9801 頁 */
    {.w_px = 25, .glyph_index = 454500}, /* U+9805 項 */
    {.w_px = 25, .glyph_index = 455250}, /* U+9808 須 */
    {.w_px = 25, .glyph_index = 456000}, /* U+9810 預 */
    {.w_px = 25, .glyph_index = 456750}, /* U+984C 題 */
    {.w_px = 25, .glyph_index = 457500}, /* U+984F 顏 */
    {.w_px = 25, .glyph_index = 458250}, /* U+985E 類 */
    {.w_px = 25, .glyph_index = 459000}, /* U+986F 顯 */
    {.w_px = 25, .glyph_index = 459750}, /* U+98A8 風 */
    {.w_px = 25, .glyph_index = 460500}, /* U+9996 首 */
    {.w_px = 25, .glyph_index = 461250}, /* U+9A30 騰 */
    {.w_px = 25, .glyph_index = 462000}, /* U+9A57 驗 */
    {.w_px = 25, .glyph_index = 462750}, /* U+9AD4 體 */
    {.w_px = 25, .glyph_index = 463500}, /* U+9AD8 高 */
    {.w_px = 25, .glyph_index = 464250}, /* U+9EC3 黃 */
    {.w_px = 25, .glyph_index = 465000}, /* U+9ED1 黑 */
    {.w_px = 25, .glyph_index = 465750}, /* U+9EDE 點 */
    {.w_px = 25, .glyph_index = 466500}, /* U+9F4A 齊 */
    {.w_px = 25, .glyph_index = 467250}, /* U+FF01 ！ */
    {.w_px = 25, .glyph_index = 468000}, /* U+FF08 （ */
    {.w_px = 25, .glyph_index = 468750}, /* U+FF09 ） */
    {.w_px = 25, .glyph_index = 469500}, /* U+FF0C ， */
    {.w_px = 25, .glyph_index = 470250}, /* U+FF0F ／ */
    {.w_px = 25, .glyph_index = 471000}, /* U+FF1A ： */
    {.w_px = 25, .glyph_index = 471750}, /* U+FF1B ； */
    {.w_px = 25, .glyph_index = 472500}, /* U+FF1F ？ */
    {.w_px = 25, .glyph_index = 473250}, /* U+FF3B ［ */
    {.w_px = 25, .glyph_index = 474000}, /* U+FF3D ］ */
};
lv_font_t cjk_tw_30 =
{
    .unicode_first = 0x2026,
    .unicode_last = 0xFF3D,
    .h_px = 30,
    .glyph_bitmap = (const uint8_t *)(NYX_RES_ADDR + 0x978B4),
    .glyph_dsc = cjk_tw_30_dsc,
    .glyph_cnt = 633,
    .unicode_list = cjk_tw_30_unicode,
    .get_bitmap = _cjk_get_bitmap,
    .get_width = _cjk_get_width,
    .bpp = 8,
    .monospace = 0,
    .next_page = NULL,
};
