import shutil

def delete_directory(path):
    if os.path.exists(path):
        shutil.rmtree(path)
