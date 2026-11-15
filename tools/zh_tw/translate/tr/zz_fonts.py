FILE = 'bdk/libs/lvgl/lv_fonts/lv_font_builtin.c'
TR = []
# 繁中字型接在 Inter 字型（含圖示字型）後面；ubuntu_mono 與 Inter 共用圖示字型，所以只需加一次
RAW = [
 ("\t/*Symbol 120*/\n#if USE_HEKATE_SYMBOL_120 != 0\n\tlv_font_add(&hekate_symbol_120, NULL);\n#endif\n}",
  "\t/*Symbol 120*/\n#if USE_HEKATE_SYMBOL_120 != 0\n\tlv_font_add(&hekate_symbol_120, NULL);\n#endif\n\n"
  "\t/* 繁體中文字型：必須最後加入，且每個大小只能加一次（否則字型鏈會形成迴圈） */\n"
  "\tlv_font_add(&cjk_tw_20, &interui_20);\n"
  "\tlv_font_add(&cjk_tw_30, &interui_30);\n}"),
]
