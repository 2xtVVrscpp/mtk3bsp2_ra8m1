EK-RA8M1用 μT-Kernel 3.0 BSP2 プロジェクト

本プロジェクトは、統合開発環境e2studio用のμT-Kernel 3.0 BSP2(Board Support Package v2)のプロジェクトです。
対象ハードウェアは、EK-RA8M1マイコンボードです。

プロジェクトの構成は以下の通りです。

- mtk3_bsp2 :    μT-Kernel 3.0 BSP2
    - mtkernel :     μT-Kernel 3.0 （OS本体）
    - doc :          ユーザーズマニュアル
    - config :       設定ファイル
    - include :      定義ファイル
    - sysdepend :    ハードウェア依存プログラム
- Application :  サンプル・アプリケーション
- その他 :        e2studioの各種ファイル


μT-Kernel 3.0 BSP2のソースコードはT-License2.2に基づきオープンソースとして公開されています。
T-License2.2の内容は以下をご覧ください。

	mtkernel/docs/TEF000-219-200401.pdf

本プロジェクトに含まれるμT-Kernel 3.0 BSP2以外のソースコードは、ルネサス エレクトロニクスのライセンス規約に従ってください。詳細は以下を参照してください。

fsp/LICENSE.txt at master · renesas/fsp · GitHub
https://github.com/renesas/fsp/blob/master/LICENSE.txt
