# How to contribute to HyperCPU project

## For collaborators:

1. Clone repository locally
2. Create new branch from the branch `master`. Think about the name - what feature are you going to add? Or are you going to fix something?
3. Work on that branch, DO NOT touching others. Every push in a non-master branch runs a CI workflow with minimal tests.
4. When the feature is ready - make a pull request to the master branch. When the PR gets created, you have to track following checks: `CodeQL`, `Codacy`, main CI workflow, that runs extended tests, and the job that builds the project on multiple distributions. Wait for the project owner to review changes and approve. In case, if MentatBot will tell you what you can improve - you better improve it:) When all CI jobs will finish successfully, wait for repository owner to merge your PR. Voila - your feature has been merged! Well done!

## For other contributors

1. Almost the same thing as for collaborators, BUT - you have to fork the repository, and work there. Notice, that you probably have to disable GitHub Actions, or connect the self-hosted runner (no guarantee that HyperCPU workflows will execute successfully on custom runner). When you are ready to send your changes - make a PR - and there goes the same cycle, until the PR gets merged:)