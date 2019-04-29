 
# This file is auto-generated from a Python script that parses a PhysiCell configuration (.xml) file.
#
# Edit at your own risk.
#
import os
from ipywidgets import Label,Text,Checkbox,Button,HBox,VBox,FloatText,IntText,BoundedIntText,BoundedFloatText,Layout,Box
    
class UserTab(object):

    def __init__(self):
        
        micron_units = Label('micron')   # use "option m" (Mac, for micro symbol)

        constWidth = '180px'
        tab_height = '500px'
        stepsize = 10

        #style = {'description_width': '250px'}
        style = {'description_width': '25%'}
        layout = {'width': '400px'}

        name_button_layout={'width':'25%'}
        widget_layout = {'width': '15%'}
        units_button_layout ={'width':'15%'}
        desc_button_layout={'width':'45%'}

        param_name1 = Button(description='random_seed', disabled=True, layout=name_button_layout)
        param_name1.style.button_color = 'lightgreen'

        self.random_seed = IntText(
          value=0,
          step=1,
          style=style, layout=widget_layout)

        param_name2 = Button(description='self_velocity_factor', disabled=True, layout=name_button_layout)
        param_name2.style.button_color = 'tan'

        self.self_velocity_factor = FloatText(
          value=0.8,
          step=0.1,
          style=style, layout=widget_layout)

        param_name3 = Button(description='neigh_velocity_factor', disabled=True, layout=name_button_layout)
        param_name3.style.button_color = 'lightgreen'

        self.neigh_velocity_factor = FloatText(
          value=0.4,
          step=0.1,
          style=style, layout=widget_layout)

        param_name4 = Button(description='previous_bias_factor', disabled=True, layout=name_button_layout)
        param_name4.style.button_color = 'tan'

        self.previous_bias_factor = FloatText(
          value=0.2,
          step=0.01,
          style=style, layout=widget_layout)

        param_name5 = Button(description='noise_factor', disabled=True, layout=name_button_layout)
        param_name5.style.button_color = 'lightgreen'

        self.noise_factor = FloatText(
          value=0.4,
          step=0.1,
          style=style, layout=widget_layout)

        param_name6 = Button(description='motile_cell_persistence_time', disabled=True, layout=name_button_layout)
        param_name6.style.button_color = 'tan'

        self.motile_cell_persistence_time = FloatText(
          value=0.05,
          step=0.01,
          style=style, layout=widget_layout)

        param_name7 = Button(description='motile_cell_migration_speed', disabled=True, layout=name_button_layout)
        param_name7.style.button_color = 'lightgreen'

        self.motile_cell_migration_speed = FloatText(
          value=0.5,
          step=0.1,
          style=style, layout=widget_layout)

        param_name8 = Button(description='wall_thickness', disabled=True, layout=name_button_layout)
        param_name8.style.button_color = 'tan'

        self.wall_thickness = IntText(
          value=5,
          step=0.1,
          style=style, layout=widget_layout)

        param_name9 = Button(description='wound_size', disabled=True, layout=name_button_layout)
        param_name9.style.button_color = 'lightgreen'

        self.wound_size = IntText(
          value=33,
          step=1,
          style=style, layout=widget_layout)

        param_name10 = Button(description='motility_threshold_pressure', disabled=True, layout=name_button_layout)
        param_name10.style.button_color = 'tan'

        self.motility_threshold_pressure = FloatText(
          value=0.4,
          step=0.1,
          style=style, layout=widget_layout)

        param_name11 = Button(description='division_threshold_pressure', disabled=True, layout=name_button_layout)
        param_name11.style.button_color = 'lightgreen'

        self.division_threshold_pressure = FloatText(
          value=0.01,
          step=0.001,
          style=style, layout=widget_layout)

        param_name12 = Button(description='relative_adhesion_strength', disabled=True, layout=name_button_layout)
        param_name12.style.button_color = 'tan'

        self.relative_adhesion_strength = FloatText(
          value=0.01,
          step=0.001,
          style=style, layout=widget_layout)

        param_name13 = Button(description='relative_repulsion_strength', disabled=True, layout=name_button_layout)
        param_name13.style.button_color = 'lightgreen'

        self.relative_repulsion_strength = FloatText(
          value=1.25,
          step=0.1,
          style=style, layout=widget_layout)

        units_button1 = Button(description='', disabled=True, layout=units_button_layout) 
        units_button1.style.button_color = 'lightgreen'
        units_button2 = Button(description='dimless', disabled=True, layout=units_button_layout) 
        units_button2.style.button_color = 'tan'
        units_button3 = Button(description='dimless', disabled=True, layout=units_button_layout) 
        units_button3.style.button_color = 'lightgreen'
        units_button4 = Button(description='dimless', disabled=True, layout=units_button_layout) 
        units_button4.style.button_color = 'tan'
        units_button5 = Button(description='dimless', disabled=True, layout=units_button_layout) 
        units_button5.style.button_color = 'lightgreen'
        units_button6 = Button(description='min', disabled=True, layout=units_button_layout) 
        units_button6.style.button_color = 'tan'
        units_button7 = Button(description='micrometer/min', disabled=True, layout=units_button_layout) 
        units_button7.style.button_color = 'lightgreen'
        units_button8 = Button(description='cells', disabled=True, layout=units_button_layout) 
        units_button8.style.button_color = 'tan'
        units_button9 = Button(description='% of assay area', disabled=True, layout=units_button_layout) 
        units_button9.style.button_color = 'lightgreen'
        units_button10 = Button(description='', disabled=True, layout=units_button_layout) 
        units_button10.style.button_color = 'tan'
        units_button11 = Button(description='', disabled=True, layout=units_button_layout) 
        units_button11.style.button_color = 'lightgreen'
        units_button12 = Button(description='dimless', disabled=True, layout=units_button_layout) 
        units_button12.style.button_color = 'tan'
        units_button13 = Button(description='dimless', disabled=True, layout=units_button_layout) 
        units_button13.style.button_color = 'lightgreen'

        desc_button1 = Button(description='', disabled=True, layout=desc_button_layout) 
        desc_button1.style.button_color = 'lightgreen'
        desc_button2 = Button(description='multiplier of self-velocity in boids equation', disabled=True, layout=desc_button_layout) 
        desc_button2.style.button_color = 'tan'
        desc_button3 = Button(description='multiplier of neighbor velocity in boids equation', disabled=True, layout=desc_button_layout) 
        desc_button3.style.button_color = 'lightgreen'
        desc_button4 = Button(description='multiplier for cell's previous bias in the boids equation', disabled=True, layout=desc_button_layout) 
        desc_button4.style.button_color = 'tan'
        desc_button5 = Button(description='random noise component in boids equation', disabled=True, layout=desc_button_layout) 
        desc_button5.style.button_color = 'lightgreen'
        desc_button6 = Button(description='time between direction changes (needs to be the mechanics time step)', disabled=True, layout=desc_button_layout) 
        desc_button6.style.button_color = 'tan'
        desc_button7 = Button(description='magnitude of velocity', disabled=True, layout=desc_button_layout) 
        desc_button7.style.button_color = 'lightgreen'
        desc_button8 = Button(description='width of boundary', disabled=True, layout=desc_button_layout) 
        desc_button8.style.button_color = 'tan'
        desc_button9 = Button(description='width of wound along x-axis', disabled=True, layout=desc_button_layout) 
        desc_button9.style.button_color = 'lightgreen'
        desc_button10 = Button(description='pressure below which cells become motile', disabled=True, layout=desc_button_layout) 
        desc_button10.style.button_color = 'tan'
        desc_button11 = Button(description='pressure below which cells divide', disabled=True, layout=desc_button_layout) 
        desc_button11.style.button_color = 'lightgreen'
        desc_button12 = Button(description='regulates cadherin strength for motile cell', disabled=True, layout=desc_button_layout) 
        desc_button12.style.button_color = 'tan'
        desc_button13 = Button(description='repulsive force exerted by wall', disabled=True, layout=desc_button_layout) 
        desc_button13.style.button_color = 'lightgreen'

        row1 = [param_name1, self.random_seed, units_button1, desc_button1] 
        row2 = [param_name2, self.self_velocity_factor, units_button2, desc_button2] 
        row3 = [param_name3, self.neigh_velocity_factor, units_button3, desc_button3] 
        row4 = [param_name4, self.previous_bias_factor, units_button4, desc_button4] 
        row5 = [param_name5, self.noise_factor, units_button5, desc_button5] 
        row6 = [param_name6, self.motile_cell_persistence_time, units_button6, desc_button6] 
        row7 = [param_name7, self.motile_cell_migration_speed, units_button7, desc_button7] 
        row8 = [param_name8, self.wall_thickness, units_button8, desc_button8] 
        row9 = [param_name9, self.wound_size, units_button9, desc_button9] 
        row10 = [param_name10, self.motility_threshold_pressure, units_button10, desc_button10] 
        row11 = [param_name11, self.division_threshold_pressure, units_button11, desc_button11] 
        row12 = [param_name12, self.relative_adhesion_strength, units_button12, desc_button12] 
        row13 = [param_name13, self.relative_repulsion_strength, units_button13, desc_button13] 

        box_layout = Layout(display='flex', flex_flow='row', align_items='stretch', width='100%')
        box1 = Box(children=row1, layout=box_layout)
        box2 = Box(children=row2, layout=box_layout)
        box3 = Box(children=row3, layout=box_layout)
        box4 = Box(children=row4, layout=box_layout)
        box5 = Box(children=row5, layout=box_layout)
        box6 = Box(children=row6, layout=box_layout)
        box7 = Box(children=row7, layout=box_layout)
        box8 = Box(children=row8, layout=box_layout)
        box9 = Box(children=row9, layout=box_layout)
        box10 = Box(children=row10, layout=box_layout)
        box11 = Box(children=row11, layout=box_layout)
        box12 = Box(children=row12, layout=box_layout)
        box13 = Box(children=row13, layout=box_layout)

        self.tab = VBox([
          box1,
          box2,
          box3,
          box4,
          box5,
          box6,
          box7,
          box8,
          box9,
          box10,
          box11,
          box12,
          box13,
        ])

    # Populate the GUI widgets with values from the XML
    def fill_gui(self, xml_root):
        uep = xml_root.find('.//user_parameters')  # find unique entry point into XML
        self.random_seed.value = int(uep.find('.//random_seed').text)
        self.self_velocity_factor.value = float(uep.find('.//self_velocity_factor').text)
        self.neigh_velocity_factor.value = float(uep.find('.//neigh_velocity_factor').text)
        self.previous_bias_factor.value = float(uep.find('.//previous_bias_factor').text)
        self.noise_factor.value = float(uep.find('.//noise_factor').text)
        self.motile_cell_persistence_time.value = float(uep.find('.//motile_cell_persistence_time').text)
        self.motile_cell_migration_speed.value = float(uep.find('.//motile_cell_migration_speed').text)
        self.wall_thickness.value = int(uep.find('.//wall_thickness').text)
        self.wound_size.value = int(uep.find('.//wound_size').text)
        self.motility_threshold_pressure.value = float(uep.find('.//motility_threshold_pressure').text)
        self.division_threshold_pressure.value = float(uep.find('.//division_threshold_pressure').text)
        self.relative_adhesion_strength.value = float(uep.find('.//relative_adhesion_strength').text)
        self.relative_repulsion_strength.value = float(uep.find('.//relative_repulsion_strength').text)


    # Read values from the GUI widgets to enable editing XML
    def fill_xml(self, xml_root):
        uep = xml_root.find('.//user_parameters')  # find unique entry point into XML 
        uep.find('.//random_seed').text = str(self.random_seed.value)
        uep.find('.//self_velocity_factor').text = str(self.self_velocity_factor.value)
        uep.find('.//neigh_velocity_factor').text = str(self.neigh_velocity_factor.value)
        uep.find('.//previous_bias_factor').text = str(self.previous_bias_factor.value)
        uep.find('.//noise_factor').text = str(self.noise_factor.value)
        uep.find('.//motile_cell_persistence_time').text = str(self.motile_cell_persistence_time.value)
        uep.find('.//motile_cell_migration_speed').text = str(self.motile_cell_migration_speed.value)
        uep.find('.//wall_thickness').text = str(self.wall_thickness.value)
        uep.find('.//wound_size').text = str(self.wound_size.value)
        uep.find('.//motility_threshold_pressure').text = str(self.motility_threshold_pressure.value)
        uep.find('.//division_threshold_pressure').text = str(self.division_threshold_pressure.value)
        uep.find('.//relative_adhesion_strength').text = str(self.relative_adhesion_strength.value)
        uep.find('.//relative_repulsion_strength').text = str(self.relative_repulsion_strength.value)
