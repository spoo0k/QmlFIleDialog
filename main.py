import pygit2
import os

workerDirectory = os.getcwd()
repoPath = pygit2.discover_repository(workerDirectory)

assert repoPath is not None, "It's noty a git repo"
repo = pygit2.Repository(repoPath)
print(repoPath)

print()
