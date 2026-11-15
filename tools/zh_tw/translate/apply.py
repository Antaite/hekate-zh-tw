# 套用翻譯：每個檔案一份 (舊字串, 新字串) 清單，比對的是含雙引號的完整 C 字串常值
import sys, os, re, importlib.util, glob
src = sys.argv[1]           # hekate 原始碼根目錄（會直接修改）
trdir = os.path.dirname(os.path.abspath(__file__)) + '/tr'
bad = 0
for tf in sorted(glob.glob(trdir + '/*.py')):
    spec = importlib.util.spec_from_file_location('t', tf); m = importlib.util.module_from_spec(spec); spec.loader.exec_module(m)
    path = os.path.join(src, m.FILE)
    s = open(path, encoding='utf8').read()
    for item in m.TR:
        old, new = item[0], item[1]
        want = item[2] if len(item) > 2 else None   # 指定預期出現次數
        q_old = '"' + old + '"'; q_new = '"' + new + '"'
        n = s.count(q_old)
        if n == 0 or (want is not None and n != want):
            print(f'[未對到] {m.FILE}: {old!r} 出現 {n} 次'); bad += 1; continue
        s = s.replace(q_old, q_new)
    for item in getattr(m, 'RAW', []):   # 非字串常值的程式碼修改（第三欄為預期次數，預設 1）
        old, new = item[0], item[1]; want = item[2] if len(item) > 2 else 1
        if s.count(old) != want:
            print(f'[程式碼未對到] {m.FILE}: {old!r} 出現 {s.count(old)} 次'); bad += 1; continue
        s = s.replace(old, new)
    open(path, 'w', encoding='utf8').write(s)
print('失敗項目數：', bad)
sys.exit(1 if bad else 0)
