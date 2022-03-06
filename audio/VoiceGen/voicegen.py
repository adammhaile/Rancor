import yaml
import fire
import os
from pathlib import Path


class VoiceGen:
    def __init__(self, config='config.yaml'):
        self.config_file = Path(config)
        self.__load_config()

    def __load_config(self):
        self.config = { 'espeak' :{
            'voice': 'english-us',
            'speed': 120,
            'pitch': 10,
            'caps':  20,
        }}
        with open(self.config_file, 'r') as cfg:
            cfg_data = yaml.load(cfg, Loader=yaml.FullLoader)

        self.config.update(cfg_data)

    def __save_config(self):
        with open(self.config_file, 'w') as cfg:
            yaml.dump(self.config, cfg)

    def __run_cmd(self, cmd):
        output = os.system(cmd)
        return output

    def __speak_cmd(self, phrase):
        cfg = self.config['espeak']
        cmd = f'espeak -v {cfg["voice"]} -s {cfg["speed"]} -p {cfg["pitch"]} -k {cfg["caps"]} "{phrase}"'
        return cmd

    def __export_cmd(self, phrase, path, name):
        base_cmd = self.__speak_cmd(phrase)
        base_cmd += f' --stdout | ffmpeg -i - -ar 44100 -ac 2 -ab 64k -f mp3 {path}/{name}.mp3'
        return base_cmd

    def __cache_write(self, phrase):
        with open('last_phrase.txt', 'w') as f:
            f.write(phrase)

    def __cache_read(self):
        with open('last_phrase.txt', 'r') as f:
            output = f.read()

        return output.strip()

    def __export(self, phrase, path, name):
        cmd = self.__export_cmd(phrase, path, name)
        # print(cmd)
        return self.__run_cmd(cmd)

    def say(self, phrase):
        """Say the given phrase"""
        cmd = self.__speak_cmd(phrase)
        self.__run_cmd(cmd)
        self.__cache_write(phrase)

    def last(self):
        phrase = self.__cache_read()
        self.say(phrase)

    def commit(self, key):
        phrase = self.__cache_read()

        if 'phrases' not in self.config:
            self.config['phrases'] = {}

        if key not in self.config['phrases']:
            self.config['phrases'][key] = []

        self.config['phrases'][key].append(phrase)

        self.__save_config()

    def export(self, path, clear=False):
        path = Path(path)
        if not path.exists() or not path.is_dir():
            print('Path must exist!')
            return

        if clear:
            for f in path.glob('*.mp3'):
                print(f'Clearing {f}')
                f.unlink()

        for group in self.config['phrases']:
            print(f'Exporting group: {group}')
            phrases = self.config['phrases'][group]
            c = 0
            for p in phrases:
                print(p)
                output = self.__export(p, path, f'{group}_{c}')
                print(output)
                c += 1


if __name__ == '__main__':
    fire.Fire(VoiceGen)
