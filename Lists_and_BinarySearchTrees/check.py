import subprocess, sys, argparse, os
import dane

def Main():
    parser = argparse.ArgumentParser()
    parser.add_argument('-p', '--program', type=str, metavar='', help='Program wykonujacy',required=True)
    parser.add_argument('-i', '--ile', type=int, metavar='', help='Ile razy ma się wykonać program',required=True)
    args = parser.parse_args()
    name = args.program
    ile = args.ile
    for i in range(ile):
        try:
            dane.Main()
        except:
            print('Nie można wczytać danych')
            print('[-] Przerywanie pracy programu')
            exit(0)
        try:
            print('[+] Wykonywanie programu "'+name+'"')
            subprocess.call('./'+name)
            print('[+] Program wykonany')
        except:
            print('[-] Nie można skompilować pliku '+name)
            print('[-] Przerywanie pracy programu')
            exit(0)


if __name__=='__main__':
    Main()
    print('[+] Sprawdzanie zakończyło się powodzeniem')
