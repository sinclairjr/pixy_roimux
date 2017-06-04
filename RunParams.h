//
// Created by damian on 6/3/17.
//

#ifndef PIXY_ROIMUX_RUNPARAMS_H
#define PIXY_ROIMUX_RUNPARAMS_H

#include <iostream>
#include <vector>

namespace pixy_roimux {
///
/// This class contains all the maps required for the VIPER pixel readout reconstruction.
/// Namely, the map from DAQ channels to readout channels and vice versa, and the mechanical coordinates of the pixels
/// and the regions of interest (ROI). It is instantiated with the run ID based on which it will generate the
/// corresponding maps. All the getter methods are const and thus an instance of this class can be passed by const
/// reference to other objects requiring it. DAQ channels are numbered from 0 to 63 with channels 0 through 31
/// corresponding to the "Ind_x" histogram in the raw data and channels 32 through 63 corresponding to the "Col_x"
/// histogram in the raw data. Caution has to be applied not to confuse those with the actual pixel collection channels
/// and ROI induction channels as the naming of the histograms is hardcoded in the DAQ driver. Additionally, this class
/// also stores all the run parameters necessary for reconstruction such as calibration constants.
///
    class RunParams {
    public:

        ///
        /// Constructor using the run ID to create the maps accordingly.
        ///
        RunParams(const unsigned t_runId);

        ///
        /// Convert DAQ channel to pixel channel.
        ///
        unsigned daq2pixel(const unsigned t_daqChan) const {
            return m_daq2readout.at(t_daqChan);
        }

        ///
        /// Convert pixel channel to DAQ channel.
        ///
        unsigned pixel2daq(const unsigned t_pixelInd) const {
            return m_readout2daq.at(t_pixelInd);
        }

        ///
        /// Convert DAQ channel to ROI channel.
        ///
        unsigned daq2roi(const unsigned t_daqChan) const {
            return m_daq2readout.at(t_daqChan) - m_nPixels;
        }

        ///
        /// Convert ROI channel to DAQ channel.
        ///
        unsigned roi2daq(const unsigned t_roiInd) const {
            return m_readout2daq.at(t_roiInd + m_nPixels);
        }

        ///
        /// Get pixel coordinates in units of pixel pitch.
        /// Pixel number 0 has the coordinates (0, 0). These are just relative offsets within one ROI. To get absolute
        /// coordinates, this number needs to be added to the according ROI coordinates obtained from GetPixelCoor. The
        /// numbering is derived from the readout PCB design.
        ///
        int getPixelCoor(
                const unsigned t_pixelInd,
                const unsigned t_dim)
        const {
            return m_pixelCoor.at(t_pixelInd).at(t_dim);
        }

        ///
        /// Get ROI coordinates in units of pixel pitch.
        /// These are offsets of pixel number 0 in the upper left corner of the ROI. To get absolut pixel coordinates, this
        /// needs to be added to the pixel coordinate obtained from GetPixelCoor. The numbering is derived from the readout
        /// PCB design.
        ///
        int getRoiCoor(
                const unsigned t_roiInd,
                const unsigned t_dim)
        const {
            return m_roiCoor.at(t_roiInd).at(t_dim);
        }

        ///
        /// Get the run ID that was used to generate the maps.
        ///
        unsigned getRunId() const {
            return m_runId;
        }

        ///
        /// Get the number of pixels.
        ///
        unsigned getNPixels() const {
            return m_nPixels;
        }

        ///
        /// Get the number of ROIs.
        ///
        unsigned getNRois() const {
            return m_nRois;
        }

        ///
        /// Get the total number of readout channels.
        /// Divided by 2 this gives the number of channels of the two DAQ histograms ("Ind_x" and "Col_x").
        ///
        unsigned getNChans() const {
            return m_nChans;
        }

        ///
        /// Get the pixel pitch in mm.
        ///
        double getPixelPitch() const {
            return m_pixelPitch;
        }

        ///
        /// Get the drift length in mm.
        ///
        double getDriftLength() const {
            return m_driftLength;
        }

        ///
        /// Get the sample time in us.
        ///
        double getSampleTime() const {
            return m_sampleTime;
        }

        ///
        /// Get the drift speed in mm/us.
        ///
        double getDriftSpeed() const {
            return m_driftSpeed;
        }

        ///
        /// Get the location of the anode in histogram samples.
        ///
        unsigned getAnodeSample() const {
            return m_anodeSample;
        }

        ///
        /// Get the ADC LSB in mV.
        ///
        double getAdcLsb() const {
            return m_adcLsb;
        }

        ///
        /// Get the preamplifier gain in mV/fC.
        ///
        double getPreampGain() const {
            return m_preampGain;
        }


    private:

        ///
        /// Run ID that is used to generate the maps.
        ///
        const unsigned m_runId;

        ///
        /// Number of pixels.
        ///
        unsigned m_nPixels;

        ///
        /// Number of ROIs.
        ///
        unsigned m_nRois;

        ///
        /// Total number of readout channels.
        ///
        unsigned m_nChans;

        ///
        /// Pixel pitch in mm.
        ///
        double m_pixelPitch;

        ///
        /// Drift length in mm.
        ///
        double m_driftLength;

        ///
        /// Sample time in us.
        ///
        double m_sampleTime;

        ///
        /// Drift speed in mm/us.
        ///
        double m_driftSpeed;

        ///
        /// Location of the anode in histogram samples.
        ///
        unsigned m_anodeSample;

        ///
        /// Analog-to-digital converter least significant bit in mV.
        /// Used to convert the value recorded by the ADC to a voltage.
        ///
        double m_adcLsb;

        ///
        /// Preamp gain in mV/fC.
        /// Used to convert the voltage recorded by the ADC to charge.
        ///
        double m_preampGain;

        ///
        /// Array mapping DAQ channels to readout channels.
        ///
        std::vector<unsigned> m_daq2readout;

        ///
        /// Array mapping readout channels to DAQ channels.
        ///
        std::vector<unsigned> m_readout2daq;

        ///
        /// Array containing the 2D pixel coordinates.
        ///
        std::vector<std::vector<int>> m_pixelCoor;

        ///
        /// Array containing the 2D ROI coordinates.
        ///
        std::vector<std::vector<int>> m_roiCoor;
    };
}


#endif //PIXY_ROIMUX_RUNPARAMS_H
