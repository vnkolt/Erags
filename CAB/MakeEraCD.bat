set ERASRC=R:\EraCD\DATA
set ERACAB=R:\EraCD.cab\DATA
cabarc N %eracab%\db.cab %erasrc%\DB\*.*
cabarc N %eracab%\Help.cab %erasrc%\Help\*.*
cabarc -r -p -P EraCD\DATA\HTML N %eracab%\HTML.cab %erasrc%\HTML\*.*
cabarc N %eracab%\Templates.cab %erasrc%\Templates\*.*
rem makecab %erasrc%\db\Helpers.mdb %eracab%\db.cab
rem makecab %erasrc%\db\FNames.txt %eracab%\db.cab