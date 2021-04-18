RAYMARCHER ET RAYTRACER GPU
 Par Dominique Michel et Lea Masselles

RAYMARCHER:

Options:   -h --help       Montre les differentes options
           -r --resolution La resolution voulue pour l'image, en pixels (image carree)
                           Valeur par defaut: 500x500 pixels
           -t --thread     Nombre de threads voulus pour executer le programme
                           Valeur par defaut: le maximum de thread possibles

Partie animation: par defaut, le Raymarcher ne genere qu'une image.
Pour generer une animation, il faut changer les variables "start", "end" et
"increment" dans le fichier "main.cc". Pour compiler les images et generer une
video, on utilise ffmpeg et la commande :
"ffmpeg -framerate <nombre de FPS> -i "RaymarcherDominiqueLea%d.ppm" RaymarcherDominiqueLea.mp4"

L'animation suivante a ete generee avec start = -10.0, end = 10.0,
increment = 0.1. [lien youtube]

/!\ Generer une animation prend du temps et beaucoup de ressources.

L'animation precedente a pris environ 1h a generer avec 24Go de RAM et un CPU
Intel Core i7 8e generation.

RAYTRACER GPU:
