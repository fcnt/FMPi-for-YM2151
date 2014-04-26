FMPi-for-YM2151
===============

YAMAHA YM2151(OPM)を搭載したFM音源ボードです。RapsberryPiをはじめとした、マイコンボードから制御して使用する事を想定しています。回路図と簡単な制御ソフトを公開しています。

![](https://raw.githubusercontent.com/fcnt/FMPi-for-YM2151/master/schematic/YM2151_Board_01-Schematic.png)


##これは何?

FM音源チップ(YAMAHA YM2151)をSPIパスに接続出来るようにしたボードです。
RaspberryPiをはじめ、SPIバスを持った様々なマイコンボードからFM音源チップを制御する事が出来ます。

##(現段階で)できること

ボードの制御シーケンスを示すためにサンプルコードを公開しています。
サンプルコードではYM2151のレジスタダンプデータを本ボードで再生することが出来ます。

##最終的なゴール

YM2151エミュレータ(http://mamedev.org/source/src/emu/sound/ym2151.c.html)
を使用したアプリから、


#使い方


