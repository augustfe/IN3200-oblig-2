# Notes for running on Fox
`ssh ec-augustfe@fox.educloud.no`

## Transfering files:
_NOTE_ `:` after adress\
Copying file to fox:\
`$ scp my_file.tar.gz ec-augustfe@fox.educloud.no:`

Use `-r` option to copy directory:\
`$ scp -r my_dir/ ec-augustfe@fox.educloud.no:/cluster/work/users/ec-augustfe/`

Copy result back:\
`$ scp -r ec-augustfe@fox.educloud.no:/cluster/work/users/ec-augustfe/my_results /home/some/place`

Unzipping files:\
`unzip my_file.zip`

Editing files:\
`emacs file.ext`, use `Control-X, Control-C` to save and exit.

## Running a job
Need a jobscript, see `example_mpi_job.script` for formula. In order to enable MPI, first run `module load OpenMPI/4.1.1-GCC-11.2.0`. Run the job by calling `sbatch example_mpi_job.script`, results will be stored in `slurm-<jobid>.out`.