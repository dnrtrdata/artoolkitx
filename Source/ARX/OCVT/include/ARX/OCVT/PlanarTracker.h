/*
 *  PlanarTracker.h
 *  artoolkitX
 *
 *  This file is part of artoolkitX.
 *
 *  artoolkitX is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  artoolkitX is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with artoolkitX.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  As a special exception, the copyright holders of this library give you
 *  permission to link this library with independent modules to produce an
 *  executable, regardless of the license terms of these independent modules, and to
 *  copy and distribute the resulting executable under terms of your choice,
 *  provided that you also meet, for each linked independent module, the terms and
 *  conditions of the license of that module. An independent module is a module
 *  which is neither derived from nor based on this library. If you modify this
 *  library, you may extend this exception to your version of the library, but you
 *  are not obligated to do so. If you do not wish to do so, delete this exception
 *  statement from your version.
 *
 *  Copyright 2018 Realmax, Inc.
 *  Copyright 2015 Daqri, LLC.
 *  Copyright 2010-2015 ARToolworks, Inc.
 *
 *  Author(s): Philip Lamb, Daniel Bell.
 *
 */

#ifndef PLANAR_TRACKER_H
#define PLANAR_TRACKER_H
#include <memory>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <ARX/AR/ar.h> // ARdouble, ARLOG
class TrackedImageInfo
{
public:
    std::shared_ptr<unsigned char> imageData;
    int uid;
    float scale;
    int width;
    int height;
    std::string fileName;
};

class PlanarTracker
{
public:
    PlanarTracker();
    ~PlanarTracker();
    PlanarTracker(PlanarTracker&&);
    PlanarTracker& operator = (PlanarTracker&&);
    
    void Initialise(ARParam cParam);

    /// Perform tracking on a single frame of video.
    /// The frame is passed as a single buffer of 8-bit greyscale pixels, starting with the top-left-most pixel
    /// of the frame and proceeding first by row, then by column. The size of the buffer must exactly match
    /// that passed in xFrameSize and yFrameSize parameters to Initialise() (i.e. xFrameSize * yFrameSize bytes).
    /// The frame data must remain valid for the entire duration of the call.
    void ProcessFrameData(unsigned char * frame);
    
    void RemoveAllMarkers();
    void AddMarker(std::shared_ptr<unsigned char> buff, std::string fileName, int width, int height, int uid, float scale);
    void AddMarker(std::string imageName, int uid, float scale);

    ///  If trackable is not visible, returns false, otherwise retrieves pose of trackable into transMat
    ///  and returns true.
    bool GetTrackablePose(int trackableId, float transMat[3][4]);
    
    bool IsTrackableVisible(int trackableId);
    bool LoadTrackableDatabase(std::string fileName);
    bool SaveTrackableDatabase(std::string fileName);
    
    bool ChangeImageId(int prevId, int newId);
    std::vector<int> GetImageIds();
    TrackedImageInfo GetTrackableImageInfo(int trackableId);
    
    void SetFeatureDetector(int detectorType);
    int GetFeatureDetector(void);

    void SetMaximumNumberOfMarkersToTrack(int maximumNumberOfMarkersToTrack);
    int GetMaximumNumberOfMarkersToTrack(void);


private:
    class PlanarTrackerImpl;
    std::shared_ptr<PlanarTrackerImpl> _trackerImpl;
    
};
#endif
