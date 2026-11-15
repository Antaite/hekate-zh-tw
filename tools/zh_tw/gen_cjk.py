#!/usr/bin/env python3
# 產生 Nyx 用的繁體中文字型：
#   1. 掃描已翻譯的 Nyx 原始碼，收集所有用到的中文字與全形標點，再加上常用字補充表
#   2. 用 Noto Sans CJK TC 畫出 20px 與 30px 兩種大小的 8 位元灰階點陣（與 Nyx 內建字型同格式）
#   3. 輸出 cjk_tw.c（字元表與寬度，編進 nyx.bin）和 cjk_glyphs.bin（點陣資料，接在 res.pak 後面）
#
# 用法：gen_cjk.py <hekate 原始碼根目錄> <輸出資料夾> <res.pak 原始大小>
import sys, os, glob
from PIL import Image, ImageDraw, ImageFont

SRC, OUT, RES_BASE = sys.argv[1], sys.argv[2], int(sys.argv[3], 0)
FONT_FILE = '/usr/share/fonts/opentype/noto/NotoSansCJK-Regular.ttc'
FONT_INDEX = 3   # Noto Sans CJK TC

# 常用字補充表：讓自訂的開機項目名稱（hekate_ipl.ini）也能顯示
EXTRA = (
    '大氣層虛擬真實原廠安全模式系統開機關機重啟主機遊戲備份還原金鑰讀取工具'
    '中文繁體簡體英日韓語言版本更新下載安裝刪除設定選單返回確定取消是否請稍候'
    '一二三四五六七八九十百千萬零壹貳參肆伍陸柒捌玖拾個月日年時分秒週星期'
    '我你他她們的了在有和與或及但因為所以如果就都也很更最已經正將會能可要想'
    '看見聽說話讀寫算用做作找到來去出入上下左右前後內外裡中間高低大小多少長短'
    '新舊快慢好壞對錯真假開關啟停送收發傳存放拿取換改變修理清除空滿全半部份'
    '電池充電量溫度風扇速效能記憶體儲存卡片硬碟網路連線無線藍牙手把控制器螢幕'
    '亮暗聲音音量畫面圖示圖片影片相簿截圖錄影文字字型主題顏色背景樣式外觀'
    '使用者帳號密碼登入登出資料夾檔案名稱路徑大小格式類型日期建立修改刪除複製移動'
    '錯誤警告提示訊息成功失敗完成進行中等待準備檢查測試掃描驗證修復清理'
    '自動手動預設自訂進階基本一般其他更多全部選項功能服務程式應用插件模組核心'
    '韌體軟體硬體晶片處理器記錄紀錄日誌報告資訊狀態詳細說明幫助關於版權'
    '測試用乙甲丙丁戊己庚辛壬癸東南西北春夏秋冬早午晚今明昨天地人心力'
    '安卓桌面相容支援不支援請注意重要危險禁止允許拒絕同意接受'
)

def collect_chars():
    chars = set()
    for f in glob.glob(os.path.join(SRC, 'nyx/nyx_gui/**/*.c'), recursive=True):
        for c in open(f, encoding='utf8').read():
            if ord(c) > 0x7E:
                chars.add(c)
    chars.update(EXTRA)
    chars.discard('﻿')
    return sorted(chars, key=ord)

def render(chars, h_px, size, center):
    font = ImageFont.truetype(FONT_FILE, size, index=FONT_INDEX)
    t, b = font.getbbox('國')[1], font.getbbox('國')[3]
    y_off = round(center - (t + b) / 2)
    dsc, blob = [], bytearray()
    for c in chars:
        w = max(1, round(font.getlength(c)))
        img = Image.new('L', (w, h_px), 0)
        ImageDraw.Draw(img).text((0, y_off), c, font=font, fill=255)
        dsc.append((ord(c), w, len(blob)))
        blob += img.tobytes()          # 每列 w 個位元組，共 h_px 列（8 位元灰階）
    return dsc, blob

def main():
    chars = collect_chars()
    # 20px：Inter 大寫字母在第 4～15 列，中心約 9.5；30px：第 5～23 列，中心約 14
    d20, b20 = render(chars, 20, 17, 9.5)
    d30, b30 = render(chars, 30, 25, 14.0)
    blob = b20 + b30
    off20, off30 = RES_BASE, RES_BASE + len(b20)

    os.makedirs(OUT, exist_ok=True)
    open(os.path.join(OUT, 'cjk_glyphs.bin'), 'wb').write(blob)

    def table(name, dsc, off):
        lines = [f'static const uint32_t {name}_unicode[] = {{']
        lines += ['    ' + ', '.join(f'0x{u:04X}' for u, _, _ in dsc[i:i + 12]) + ',' for i in range(0, len(dsc), 12)]
        lines += ['};', f'static const lv_font_glyph_dsc_t {name}_dsc[] = {{']
        lines += [f'    {{.w_px = {w}, .glyph_index = {gi}}}, /* U+{u:04X} {chr(u)} */' for u, w, gi in dsc]
        lines += ['};']
        lines += [f'lv_font_t {name} =', '{',
                  f'    .unicode_first = 0x{dsc[0][0]:04X},',
                  f'    .unicode_last = 0x{dsc[-1][0]:04X},',
                  f'    .h_px = {20 if name.endswith("20") else 30},',
                  f'    .glyph_bitmap = (const uint8_t *)(NYX_RES_ADDR + 0x{off:X}),',
                  f'    .glyph_dsc = {name}_dsc,',
                  f'    .glyph_cnt = {len(dsc)},',
                  f'    .unicode_list = {name}_unicode,',
                  '    .get_bitmap = _cjk_get_bitmap,',
                  '    .get_width = _cjk_get_width,',
                  '    .bpp = 8,',
                  '    .monospace = 0,',
                  '    .next_page = NULL,',
                  '};', '']
        return '\n'.join(lines)

    c = f'''/*
 * 繁體中文字型（由 tools/zh_tw/gen_cjk.py 自動產生，請勿手動修改）
 * 字型來源：Noto Sans CJK TC（SIL Open Font License 1.1）
 * 共 {len(chars)} 個字；點陣資料放在 res.pak 的 0x{RES_BASE:X} 之後。
 */

#include "../lv_misc/lv_font.h"
#include <memory_map.h>

/* 字元表已依編碼排序，用二分搜尋找字，比內建的逐一比對快很多 */
static int _cjk_find(const lv_font_t *font, uint32_t letter)
{{
    if (letter < font->unicode_first || letter > font->unicode_last)
        return -1;

    int lo = 0, hi = font->glyph_cnt - 1;
    while (lo <= hi)
    {{
        int mid = (lo + hi) >> 1;
        uint32_t u = font->unicode_list[mid];
        if (u == letter)
            return mid;
        if (u < letter)
            lo = mid + 1;
        else
            hi = mid - 1;
    }}

    return -1;
}}

static const uint8_t *_cjk_get_bitmap(const lv_font_t *font, uint32_t letter)
{{
    int i = _cjk_find(font, letter);
    return i < 0 ? NULL : &font->glyph_bitmap[font->glyph_dsc[i].glyph_index];
}}

static int16_t _cjk_get_width(const lv_font_t *font, uint32_t letter)
{{
    int i = _cjk_find(font, letter);
    return i < 0 ? -1 : font->glyph_dsc[i].w_px;
}}

{table('cjk_tw_20', d20, off20)}
{table('cjk_tw_30', d30, off30)}'''
    open(os.path.join(OUT, 'cjk_tw.c'), 'w', encoding='utf8').write(c)
    open(os.path.join(OUT, 'charset.txt'), 'w', encoding='utf8').write(''.join(chars) + '\n')
    print(f'字數：{len(chars)}，點陣大小：20px {len(b20)} 位元組，30px {len(b30)} 位元組，'
          f'res.pak 會從 {RES_BASE} 增加到 {RES_BASE + len(blob)} 位元組')

main()
