#include <iostream>
#include <fstream>
#include <string>

#define DEFAULTFILE "data.txt"

using namespace std;
//�g�� ���O��� std
//���@�̌��t�@���O���[std]����ɗL���ɂ���̂�std::���ȗ��ł���悤�ɂȂ�B
//std::cin -> cin 
//�����b�g:�킩��₷���Ȃ�B
//�f�����b�g:�����ʂ̖��O��Ԃ�錾�����ꍇ�A�u���������v�Łu�������O�v�̊֐��Ȃǂ�����Ƃ��ɁA
// �ǂ���̊֐����R���p�C������킩��Ȃ��Ȃ�̂ŁB�R���p�C���G���[���o�Ă��܂��B
// using std::cin;�@�̂悤�ɓ���̊֐����݂̂��w�肷��̂��]�܂����B

string randstr(int digits) {//�����Ń����_���ȕ�����𐶐��i�\���g�p�j
	string result;
	int random = 0;
	char desc[] = {//�����e�[�u��
	'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O',
	'P','Q','R','S','T','U','V','W','X','Y','Z','0','1','2','3',
	'4','5','6','7','8','9'
	};
	srand(time(NULL));
	for (int i = 0; i < digits; i++) {
		random = rand() % 36;//������
		result = desc[random] + result;//�����e�[�u���z��̕����𕶎���ɒǉ�
	}
	return result;
}

int main(void) {
	string s;
	cout << "���[�h��I��ł��������B" << endl << "1.�o�^\t2.���O�C��" << endl;
	//���j���[��ʂ̕\��
	//std::cout �W���o�͂ɏo��
	//std::endl ���s 
	cin >> s;
	//���[�h�̎擾
	//std::cin �W�����͂���擾
	bool loop = true;
	while (loop) {
		if (s == "1") {
			ifstream ifs(DEFAULTFILE);
			bool check = true;
			while (check)
			{
				cout << "���[�U�[������͂��Ă��������B:";
				cin >> s;
				if (!ifs.is_open()) {
					break;
				}
				else {
					ifs.seekg(SEEK_SET);
					while (!ifs.eof()) {//�f�[�^�t�@�C�����瓯�����[�U�[����T��
						string buff;
						getline(ifs, buff);
						if (s == buff.substr(0, buff.find(" "))) {
							//�������[�U�[�������݂���
							cout << "���̃��[�U�[���͂��łɎg�p����Ă��܂��B" << endl;
							break;
						}
					}
					//�������[�U�[�������݂��Ȃ�
					if (ifs.eof()) check = false;
				}
			}
			ifs.close();
			ofstream ofs(DEFAULTFILE, ios::ate | ios::app);
			//���[�U�[�����������ށB
			ofs << s << " ";
			cout << "�p�X���[�h����͂��Ă��������B:";
			cin >> s;
			string salt;
			//�\���g����
			salt = randstr(20);
			//�\���g�ƃp�X���[�h����������B�����A�Ƃ���
			s = salt + s;
			//�n�b�V��������A���t�@�C���ɏ�������
			ofs << hash<string>()(s) << salt << endl;
			//�F�؂ɐi�ނ��m�F
			cout << "�����ă��O�C�����܂����H" << endl << "yes or no" << endl;
			cin >> s;
			ofs.close();
			//�uyes�v�܂��́uYES�v�܂��́u�͂��v�Ɠ��͂��ꂽ�Ƃ�
			if (s == "yes" || s == "YES" || s == "�͂�") {
				//���s����B
				s = "2";
				loop = true;
			}
			//�łȂ���΁@�I������
			else loop = false;
		}
		else if (s == "2") {
			string buff;
			cout << "���[�U�[������͂��Ă��������B:";
			cin >> s;
			ifstream ifs(DEFAULTFILE);
			ifs.seekg(SEEK_SET);
			while (!ifs.eof()) {
				//��v���郆�[�U�[���̒T��
				getline(ifs, buff);
				if (s == buff.substr(0, buff.find(" "))) {
					break;
				}
			}
			cout << "�p�X���[�h����͂��Ă��������B:";
			cin >> s;
			string buff2 = buff;
			//�t�@�C�����\���g���擾
			buff2.erase(0, buff2.length()-20);
			//���͂��ꂽ�p�X���[�h�ƃ\���g������ �����B�Ƃ���B
			s = buff2+s;
			//�n�b�V�������ꂽ�p�X���[�h�ƃ\���g�݂̂ɂ���
			buff.erase(0, buff.find(" ") + 1);
			//�n�b�V�������ꂽ�p�X���[�h���擾
			buff=buff.substr(0,buff.length()-20);
			//�n�b�V�������ꂽ�p�X���[�h�ƃn�b�V��������A���r����
			if (to_string(hash<string>()(s)) == buff && !ifs.eof()) {
				//��v�����Ȃ�
				cout << "�F�ؐ����I�I";
				cin.get();
			}
			else {
				//�s��v�Ȃ��
				cout << "���[�U�[���܂��̓p�X���[�h���Ⴂ�܂��B" << endl;
				cin.get();
			}
			loop = false;
			ifs.close();
		}
	}
	return 0;
}