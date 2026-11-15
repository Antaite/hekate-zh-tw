#!/usr/bin/env python3
# 產生繁中版 res.pak：官方 hekate 6.5.5 的 res.pak 後面接上中文字型點陣
# 用法：build_res.py <官方 res.pak> <中文點陣 cjk_glyphs.bin> <輸出 res.pak>
import sys, hashlib
OFFICIAL_MD5 = '3a231939926031306e360a7c0780c7e5'   # hekate 6.5.5 官方 res.pak
RES_BASE = 0x63000                                   # 中文點陣起點，必須和 cjk_tw.c 一致
src, glyphs, out = sys.argv[1:4]
base = open(src, 'rb').read()
if hashlib.md5(base).hexdigest() != OFFICIAL_MD5:
    sys.exit('官方 res.pak 的檢查碼不符，請確認版本')
if len(base) > RES_BASE:
    sys.exit('官方 res.pak 比預留位置大，中文點陣會蓋到原本的資料')
data = base + b'\0' * (RES_BASE - len(base)) + open(glyphs, 'rb').read()
if len(data) > 16 * 1024 * 1024:
    sys.exit('res.pak 超過 16MB 上限')
open(out, 'wb').write(data)
print(f'res.pak 完成：{len(data)} 位元組')
