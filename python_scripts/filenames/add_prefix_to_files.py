import os
import copy
base_path = r'C:\unreal_projects\RTS\Models\Characters\animation\GirlLocomotion'
prefix = 'FemaleLocomotion_30_'
input_filenames = [el for el in os.listdir(base_path)]
input_paths = [os.path.join(el) for el in os.listdir(base_path)]

# apply filters to file names
for src_filename in input_filenames:
    src_path = os.path.join(base_path, src_filename)
    t_filename = copy.deepcopy(src_filename)
    # to lowercase
    t_filename = t_filename.lower()
    # replace
    t_filename = t_filename.replace(' ', '_')
    t_filename = t_filename.replace('(', '_')
    t_filename = t_filename.replace(')', '_')
    # add prefix
    t_filename = prefix + t_filename
    o_path = os.path.join(base_path, t_filename)
    os.rename(src_path, o_path)

