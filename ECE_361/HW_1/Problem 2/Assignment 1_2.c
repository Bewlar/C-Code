Question 2 (15 pts): Short Answers
a. [5] Provide a concise (a few sentences) answer for these questions:

1) What does it mean to make a “commit” to a git repository?
A commit is a revision update to a file or multiple set of files.
The commit is a unique "hash" that keeps record of changes with who and when and can include descriptions.
The commit pushes changes in the staging area and puts them in a local repository.

2) What is the role of the “staging area” in a git repository?
The role of the staging area is a preparation location which will be part of the next commit.
Files can be sent to the staging area and reviewed by others before all files are committed.
The role is to be a preparation before changes are pushed as a whole.

3) How do you use the “staging area” to control what files you are committing to a repository?
To use the git staging area you can use git status to check files which will be committed.
Adding files to the staging area is done through git add <file> command.
If files are edited you can check if they will update the changes in the commit using git status again.
Git diff can also show what has been changed but not staged.
To finalize and send the staging area to the local repository, you can use the git commit command.
To remove any files from staging git rm command will remove the file.


b. [5] GitHub provides a cloud-based host for your repositories.
Describe the process (you can include/discuss the relevant git commands if you’d like) to push your local repositories to “the cloud.”
Github works using the process in Git of branching which is similar to staging or generating a preparatory code.
Branching is a separate workflow from the main trunk allowing users to test features before committing.
Committing pushes your edits to the staging area.
Pull requests are for discussions. They are visible new code pieces that haven't yet been committed.
The next stage is discussing and reviewing code. After errors are complete, the branch can be pushed.
Finally, the branch can also be deployed from github which is testing a branch. If there are errors the deployed version can be rolled back to the existing main branch.
After testing is complete, the code can be merged into production.

Code for cloud repositories
Initialize a local directory as git repository (Git init)
Add the files to new local repository for staging (git add)
Commit the staging (git commit "comments" )
Remote add to cloud (git remote add origin repository URL)
Push all changes (git push origin master)

c. [5] What is a branch in git and how do you create one?
Give an example of how a branch can be used to debug a new code module without risking your working code.
A branch in git is a pointer to a commit(snapshot of changes).
An example could be a disc drive that has a new interface that needs to change.
The testing group could create a new branch from the existing main code using git branch testcode.
This will generate new code to debug and work on without changing the main.
The user can use git checkout testcode to move to the new code.
After finishing the hotfix or bug, the user can use git checkout master.
Then they can merge the hotfix or debug code using git merge testcode or not use it at all.
