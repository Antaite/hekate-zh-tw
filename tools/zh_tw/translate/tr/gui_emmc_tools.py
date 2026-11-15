FILE = 'nyx/nyx_gui/frontend/gui_emmc_tools.c'
TR = [
 ("  Restore ", "  還原"),
 ("  Backup ", "  備份"),
 ("  Backup eMMC", "  備份 eMMC"),   # 必須和 gui_tools.c 的按鈕文字一致
 (" Backup", " 備份"),
 (" Restore", " 還原"),
 ("Full", "完整"),
 ("Allows you to backup the BOOT physical partitions.\\n", "備份 BOOT 實體分割區，\\n"),
 ("They contain the BCT, keys and various package1.\\n", "內含 BCT、金鑰和各種 package1。\\n", 2),
 ("#FF8000 These are paired with the RAW GPP backup.#", "#FF8000 要和 RAW GPP 備份搭配使用。#"),
 ("Allows you to restore the BOOT physical partitions.\\n", "還原 BOOT 實體分割區，\\n"),
 ("#FF8000 These are paired with the RAW GPP restore.#", "#FF8000 要和 RAW GPP 還原搭配使用。#"),
 ("Allows you to backup the GPP physical partition.\\n", "備份 GPP 實體分割區，\\n"),
 ("It contains, CAL0, various package2, SYSTEM, USER, etc.\\n", "內含 CAL0、各種 package2、SYSTEM、USER 等。\\n", 3),
 ("#FF8000 This is paired with the BOOT0/1 backups.#", "#FF8000 要和 BOOT0/1 備份搭配使用。#"),
 ("Allows you to restore the GPP physical partition.\\n", "還原 GPP 實體分割區，\\n"),
 ("#FF8000 This is paired with the BOOT0/1 restore.#", "#FF8000 要和 BOOT0/1 還原搭配使用。#"),
 ("GPP Partitions", "GPP 分割區"),
 ("Allows you to backup the partitions from RAW GPP except\\n", "備份 RAW GPP 裡除了 USER 以外的分割區，\\n"),
 ("USER. It contains, CAL0, various package2, SYSTEM, etc.\\n", "內含 CAL0、各種 package2、SYSTEM 等。\\n"),
 ("#FF8000 This is an incomplete backup.#", "#FF8000 這不是完整備份。#"),
 ("Allows you to restore ALL partitions from RAW GPP\\n", "還原 RAW GPP 裡的所有分割區，\\n"),
 ("Allows you to backup the USER partition from RAW GPP.\\n", "備份 RAW GPP 裡的 USER 分割區。\\n"),
 ("#FF8000 This is an incomplete backup.#\\n", "#FF8000 這不是完整備份。#\\n"),
 (" SD emuMMC Raw Partition", " SD 虛擬系統原始分割區"),
]
# 啟用 UTF-8 之後圖示符號變成 3 個位元組：原本「跳過 1 位元組圖示＋2 個空白」改成跳過 5 個位元組
RAW = [
 ("win_label+3);", "win_label+5);"),
]
