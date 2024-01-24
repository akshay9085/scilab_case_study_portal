<?php
function download_proposal_abstract() {
	$proposal_id = arg(3);
	$root_path = scilab_case_study_path();
	$query = db_select('case_study_proposal');
	$query->fields('case_study_proposal');
	$query->condition('id', $proposal_id);
	$result = $query->execute();
	$scilab_case_study_project_files = $result->fetchObject();
	$directory_name = $scilab_case_study_project_files->directory_name . '/';
	$str = substr($scilab_case_study_project_files->samplefilepath, strrpos($scilab_case_study_project_files->samplefilepath, '/'));
    $abstract_file = ltrim($str, '/');
	ob_clean();
	header("Pragma: public");
	header("Expires: 0");
	header("Cache-Control: must-revalidate, post-check=0, pre-check=0");
	header("Cache-Control: public");
	header("Content-Description: File Transfer");
	header("Content-Type: application/pdf");
	header('Content-disposition: attachment; filename="' . $abstract_file . '"');
	header("Content-Length: " . filesize($root_path . $scilab_case_study_project_files->samplefilepath));
	header("Content-Transfer-Encoding: binary");
	header("Expires: 0");
	header("Pragma: no-cache");
	readfile($root_path . $scilab_case_study_project_files->samplefilepath);
	ob_end_flush();
	ob_clean();
}

function scilab_case_study_download_final_report() {
	$proposal_id = arg(3);
	$root_path = scilab_case_study_path();
	$query = db_select('case_study_proposal');
	$query->fields('case_study_proposal');
	$query->condition('id', $proposal_id);
	$result = $query->execute();
	$scilab_case_study_project_files = $result->fetchObject();
	$query = db_select('case_study_submitted_abstracts_file');
	$query->fields('case_study_submitted_abstracts_file');
	$query->condition('proposal_id', $id);
	$query->condition('filetype', 'A');
	$project_files = $query->execute();
	$final_report_data = $project_files->fetchObject();
	$directory_name = $scilab_case_study_project_files->directory_name . '/project_files/';
	/*$str = substr($scilab_case_study_project_files->samplefilepath, strrpos($scilab_case_study_project_files->samplefilepath, '/'));
    $abstract_file = ltrim($str, '/');*/
	ob_clean();
	header("Pragma: public");
	header("Expires: 0");
	header("Cache-Control: must-revalidate, post-check=0, pre-check=0");
	header("Cache-Control: public");
	header("Content-Description: File Transfer");
	header("Content-Type: application/pdf");
	header('Content-disposition: attachment; filename="' . $final_report_data->filename . '"');
	header("Content-Length: " . filesize($root_path . $directory_name . $final_report_data->filename));
	header("Content-Transfer-Encoding: binary");
	header("Expires: 0");
	header("Pragma: no-cache");
	readfile($root_path . $directory_name . $final_report_data->filename);
	ob_end_flush();
	ob_clean();
}