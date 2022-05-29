#include <iostream>
#include <fstream>
#include <string>

#define DEFAULTFILE "data.txt"

using namespace std;
//使う 名前空間 std
//魔法の言葉　名前空間[std]を常に有効にするのでstd::を省略できるようになる。
//std::cin -> cin 
//メリット:わかりやすくなる。
//デメリット:複数別の名前空間を宣言した場合、「同じ引数」で「同じ名前」の関数などがあるときに、
// どちらの関数かコンパイラからわからなくなるので。コンパイルエラーが出てしまう。
// using std::cin;　のように特定の関数等のみを指定するのが望ましい。

string randstr(int digits) {//乱数でランダムな文字列を生成（ソルト用）
	string result;
	int random = 0;
	char desc[] = {//文字テーブル
	'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O',
	'P','Q','R','S','T','U','V','W','X','Y','Z','0','1','2','3',
	'4','5','6','7','8','9'
	};
	srand(time(NULL));
	for (int i = 0; i < digits; i++) {
		random = rand() % 36;//文字列
		result = desc[random] + result;//文字テーブル配列の文字を文字列に追加
	}
	return result;
}

int main(void) {
	string s;
	cout << "モードを選んでください。" << endl << "1.登録\t2.ログイン" << endl;
	//メニュー画面の表示
	//std::cout 標準出力に出力
	//std::endl 改行 
	cin >> s;
	//モードの取得
	//std::cin 標準入力から取得
	bool loop = true;
	while (loop) {
		if (s == "1") {
			ifstream ifs(DEFAULTFILE);
			bool check = true;
			while (check)
			{
				cout << "ユーザー名を入力してください。:";
				cin >> s;
				if (!ifs.is_open()) {
					break;
				}
				else {
					ifs.seekg(SEEK_SET);
					while (!ifs.eof()) {//データファイルから同じユーザー名を探索
						string buff;
						getline(ifs, buff);
						if (s == buff.substr(0, buff.find(" "))) {
							//同じユーザー名が存在する
							cout << "そのユーザー名はすでに使用されています。" << endl;
							break;
						}
					}
					//同じユーザー名が存在しない
					if (ifs.eof()) check = false;
				}
			}
			ifs.close();
			ofstream ofs(DEFAULTFILE, ios::ate | ios::app);
			//ユーザー名を書き込む。
			ofs << s << " ";
			cout << "パスワードを入力してください。:";
			cin >> s;
			string salt;
			//ソルト生成
			salt = randstr(20);
			//ソルトとパスワードを結合する。これをAとする
			s = salt + s;
			//ハッシュ化したAをファイルに書き込む
			ofs << hash<string>()(s) << salt << endl;
			//認証に進むか確認
			cout << "続いてログインしますか？" << endl << "yes or no" << endl;
			cin >> s;
			ofs.close();
			//「yes」または「YES」または「はい」と入力されたとき
			if (s == "yes" || s == "YES" || s == "はい") {
				//続行する。
				s = "2";
				loop = true;
			}
			//でなければ　終了する
			else loop = false;
		}
		else if (s == "2") {
			string buff;
			cout << "ユーザー名を入力してください。:";
			cin >> s;
			ifstream ifs(DEFAULTFILE);
			ifs.seekg(SEEK_SET);
			while (!ifs.eof()) {
				//一致するユーザー名の探索
				getline(ifs, buff);
				if (s == buff.substr(0, buff.find(" "))) {
					break;
				}
			}
			cout << "パスワードを入力してください。:";
			cin >> s;
			string buff2 = buff;
			//ファイルよりソルトを取得
			buff2.erase(0, buff2.length()-20);
			//入力されたパスワードとソルトを結合 これをBとする。
			s = buff2+s;
			//ハッシュ化されたパスワードとソルトのみにする
			buff.erase(0, buff.find(" ") + 1);
			//ハッシュ化されたパスワードを取得
			buff=buff.substr(0,buff.length()-20);
			//ハッシュ化されたパスワードとハッシュ化したAを比較する
			if (to_string(hash<string>()(s)) == buff && !ifs.eof()) {
				//一致したなら
				cout << "認証成功！！";
				cin.get();
			}
			else {
				//不一致ならば
				cout << "ユーザー名またはパスワードが違います。" << endl;
				cin.get();
			}
			loop = false;
			ifs.close();
		}
	}
	return 0;
}